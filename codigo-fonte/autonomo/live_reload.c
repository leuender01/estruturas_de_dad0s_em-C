#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <pthread.h>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

#define WS_PORT 8001 //porta do web socket
#define PORT 8002 //porta a onde os arquivos html, js, css serao comunicados
#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUFFER_LEN (1024 * (EVENT_SIZE + 16))
#define LOCAL_HOST "127.0.0.1"

char *html(const char *nome_arquivo, const char *type);//pega os arquivos
void *notificacao(void *arg);//função que monitora apenas o difertorio atual
void *websocket(void *arg); //funçao que roda o servidor websocket 
void calcular_chave_websocket(const char *key, char *output);//calcula chave
                                                             
const char erro404[] = "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n";
volatile int ws_connection_fd = -1; //variavel global que controla o fluxo de carregamanto

int main(void)
{
    int socket_fd, connection_fd;
    struct sockaddr_in myserve, client;
    char input[1024];
    
    socklen_t client_size = (socklen_t)sizeof(client);
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    if(socket_fd > 0) printf("Socket aberto\n"); 
    
    myserve.sin_family = AF_INET;
    myserve.sin_port = htons(PORT);
    myserve.sin_addr.s_addr = INADDR_ANY;
    inet_aton(LOCAL_HOST, &(myserve.sin_addr));
   
    printf("tentando abrira porta %i\n",PORT); 
            
    if(bind(socket_fd, (struct sockaddr*)&myserve, sizeof(myserve)) != 0)
    {
        printf("houve um problema em abrir a porta\n");
        return 0;
    }
    printf("Abrindo a porta %i\n", PORT);
    listen(socket_fd, 3);
    printf("ouvindo a porta %i e esperando..\n", PORT);

    pthread_t id_monitor;
    pthread_create(&id_monitor, NULL, notificacao, NULL);

    pthread_t id_websocket;
    pthread_create(&id_websocket, NULL, websocket, NULL);
    

    usleep(500000);//espera o socket dar bind 
    
    while(1)
    {
        connection_fd = accept(socket_fd, (struct sockaddr*)&client, &client_size);
        memset(input, 0 , sizeof(input));
        read(connection_fd, input, sizeof(input));

        char ip_client[INET_ADDRSTRLEN];
        inet_ntop( AF_INET, &(client.sin_addr), ip_client, INET_ADDRSTRLEN );
        printf("IP que enviou: %s\n", ip_client);
        printf("Enviando mensagem de retorno\n");
        char *resposta = NULL;
        if(strstr(input, "GET /script.js"))  resposta = html("script.js", "text/javascript");
        else if(strstr(input, "GET /style.css"))  resposta = html("style.css", "text/css");
        else if(strstr(input, "GET /"))  resposta = html("index.html", "text/html");

        if(resposta != NULL)
        {
            write(connection_fd, resposta, strlen(resposta));
            free(resposta);
        }else
        {
            write(connection_fd, erro404, strlen(erro404));
        }
        close(connection_fd);
    
    }
    close(socket_fd);

    return 0;
}

char *html(const char *nome_arquivo, const char *type)
{
    char cabecalho[234];
    FILE *arquivo = fopen(nome_arquivo, "rb");
    if(arquivo == NULL  )
    {
        perror("Erro abrir arquivo");
        return NULL;
    }
    rewind(arquivo);
    fseek(arquivo, 0, SEEK_END);
    long tamanho_bytes = ftell(arquivo);
    rewind(arquivo);

    char *buffer = (char *)malloc(tamanho_bytes + 1);
    if(buffer == NULL)
    {
        perror("erro alocar memoria");
        fclose(arquivo);
        return NULL;

    }
    size_t bytes_lidos = fread(buffer, 1, tamanho_bytes ,arquivo);
    if(bytes_lidos != tamanho_bytes)
    {
        perror("Erro ao ler arquivo");
        free(buffer);
        fclose(arquivo);
        return NULL;
    } 
    fclose(arquivo);
    buffer[tamanho_bytes] = '\0';
    sprintf(cabecalho,"HTTP/1.1 200 OK\r\nContent-Type: %s\r\nContent-Length: %li\r\nConnection: close\r\n\r\n" , type,tamanho_bytes);
    char *resposta = malloc(strlen(buffer) + strlen(cabecalho) + 1);
    
    strcpy(resposta, cabecalho);
    strcat(resposta,buffer);
  
    free(buffer);
    return resposta;
}

void *notificacao(void *arg)
{
    char buffer[BUFFER_LEN]; 
    int fd = inotify_init();
    inotify_add_watch(fd, ".", IN_MODIFY | IN_CLOSE_WRITE);

    while(1)
    {
        int lenght = read(fd, buffer, BUFFER_LEN);
        if(lenght <  0)
        {
            perror("Erro de leitura");
            break;
        }
        
        int i = 0;
        while(i < lenght)
        {
            struct inotify_event *event = (struct inotify_event *) &buffer[i];
            if(event->len)
            {
                if (strcmp(event->name, "index.html") == 0 || 
                    strcmp(event->name, "style.css") == 0 || 
                    strcmp(event->name, "script.js") == 0) 
                {
                        printf("Arquivo modificado: %s\n", event->name);
                        if(ws_connection_fd != -1)
                        {
                            char ws_frame[8] = {0x81, 0x06, 'r','e','l','o','a','d'};
                            if(write(ws_connection_fd, ws_frame, 8) < 0)
                            {
                                printf("[WS] Conexao perdida com o navegador.\n");
                                close(ws_connection_fd);
                                ws_connection_fd = -1;
                            }else{
                                printf("[WS] Comando 'reload' enviado com sucesso!\n");
                        }
                    } 
                }
            }
            i+= EVENT_SIZE + event->len;
        } 
    }
    close(fd);
    return NULL;
}

void *websocket(void *arg)
{
    int ws_socket_fd, connection_fd;
    struct sockaddr_in ws_serve, client;
    socklen_t client_size = (socklen_t)sizeof(client);
    char input[1024];
    int opt = 1;

    ws_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(ws_socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    ws_serve.sin_family = AF_INET;
    ws_serve.sin_port = htons(WS_PORT);
    ws_serve.sin_addr.s_addr = INADDR_ANY;

    if(bind(ws_socket_fd, (struct sockaddr*)&ws_serve, sizeof(ws_serve)) != 0) {
        printf("Erro ao abrir a porta WebSocket\n");
        return NULL;
    }
    listen(ws_socket_fd, 3);
    printf("Servidor WebSocket aguardando na porta %i\n", WS_PORT);

    while(1) {
        connection_fd = accept(ws_socket_fd, (struct sockaddr*)&client, &client_size);
        
        memset(input, 0, sizeof(input));
        read(connection_fd, input, sizeof(input) - 1);
        printf("RSPOSTA DO SOCKET: %s\n", input);
        char *key_start = strstr(input, "Sec-WebSocket-Key: ");
        if(key_start != NULL){
            key_start += 19; // Pula o texto "Sec-WebSocket-Key: "
            
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
            ws_connection_fd = connection_fd; 
            printf("[WS] Conexão aceita e mantida aberta!\n\n");
      
        } else {
            write(connection_fd, erro404, strlen(erro404));
            printf("[WS] Requisição inválida recebida na porta %d (Falta a chave).\n", WS_PORT);
            close(connection_fd);
            
        }
    }
    return NULL;
}

void calcular_chave_websocket(const char *key, char *output) {
    char GUID[] = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
    char buffer[256];
    unsigned char sha1_result[SHA_DIGEST_LENGTH];

    memset(buffer, 0, sizeof(buffer));
    memset(sha1_result, 0, sizeof(sha1_result));
    sprintf(buffer, "%s%s", key, GUID);


    SHA1((unsigned char*)buffer, strlen(buffer), sha1_result);

    BIO *bio, *b64;
    BUF_MEM *buffer_ptr;

    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
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
