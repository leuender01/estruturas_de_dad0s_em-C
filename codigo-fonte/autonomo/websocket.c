#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

#define WS_PORT 3002 //rodara na nessa porta pode ser trocado

void calcular_chave_websocket(const char *key, char *output);



int main(void)
{
    int ws_socket_fd, connection_fd;
    struct sockaddr_in ws_serve, client;
    socklen_t client_size = (socklen_t)sizeof(client);
    char input[1024];

    ws_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(ws_socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    ws_serve.sin_family = AF_INET;
    ws_serve.sin_port = htons(WS_PORT);
    ws_serve.sin_addr.s_addr = INADDR_ANY;

    if(bind(ws_socket_fd, (struct sockaddr*)&ws_serve, sizeof(ws_serve)) != 0) {
        printf("Erro ao abrir a porta WebSocket\n");
        return 0;
    }
    listen(ws_socket_fd, 5);
    printf("Servidor WebSocket aguardando na porta %i\n", WS_PORT);

    while(1) {
        connection_fd = accept(ws_socket_fd, (struct sockaddr*)&client, &client_size);
        
        memset(input, 0, sizeof(input));
        read(connection_fd, input, sizeof(input) - 1);
        char *key_start = strstr(input, "Sec-WebSocket-Key: ");
        if(key_start != NULL){
            key_start += 19; 
            
            char client_key[64];
            memset(client_key, 0, sizeof(client_key));

            int k = 0;
            while (key_start[k] != '\r' && key_start[k] != '\n' && key_start[k] != ' ' && k < 32) {
                client_key[k] = key_start[k];
                k++;
            }
            client_key[k] = '\0';

            printf("[WS] Chave recebida do Firefox: '%s' (Tamanho: %d)\n", client_key, (int)strlen(client_key));

            char chave_aceita[128];
            memset(chave_aceita, 0, sizeof(chave_aceita));
            calcular_chave_websocket(client_key, chave_aceita);

            printf("[WS] Chave Base64 gerada: '%s'\n", chave_aceita);
            char response[1024];
            memset(response, 0, sizeof(response));
            
            
            strcat(response, "HTTP/1.1 101 Switching Protocols\r\n");
            strcat(response, "Upgrade: websocket\r\n");
            strcat(response, "Connection: Upgrade\r\n");
            sprintf(response + strlen(response), "Sec-WebSocket-Accept: %s\r\n\r\n", chave_aceita);
            write(connection_fd, response, strlen(response));            
 
            printf("[WS] Conexão aceita e mantida aberta!\n\n");
      
        } else {
            printf("[WS] Requisição inválida recebida na porta %d (Falta a chave).\n", WS_PORT);
            close(connection_fd);
            
        }
    }
    
    return 0;
}

void calcular_chave_websocket(const char *key, char *output) {
    char GUID[] = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
    char buffer[256];
    unsigned char sha1_result[SHA_DIGEST_LENGTH];

    // 1. Junta a chave do navegador com o GUID padrão universal
    memset(buffer, 0, sizeof(buffer));
    memset(sha1_result, 0, sizeof(sha1_result));
    sprintf(buffer, "%s%s", key, GUID);

    // 2. Calcula o Hash SHA-1
    SHA1((unsigned char*)buffer, strlen(buffer), sha1_result);

    // 3. Converte o resultado do SHA-1 para Base64
    BIO *bio, *b64;
    BUF_MEM *buffer_ptr;

    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL); // Remove quebras de linha
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_write(bio, sha1_result, SHA_DIGEST_LENGTH);
    BIO_flush(bio);

    bio = BIO_pop(b64);

    BIO_get_mem_ptr(bio, &buffer_ptr);

    memcpy(output, buffer_ptr->data, buffer_ptr->length);
    output[buffer_ptr->length] = '\0';

    BIO_free_all(bio);
    BIO_free(b64);
}
