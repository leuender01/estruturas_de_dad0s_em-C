#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>


#define SERVE_IP "127.0.0.1"
#define PORT 3002
#define BUFFER_SIZE 1024

void enviar_mensagem_ws(int fd, const char *texto);
const char b64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
void base64_encode_16bytes(const unsigned char *input, char *output);
void gerar_bytes_aleatorios(unsigned char *buffer);
            
int main(void)
{
    int soocket;
    struct sockaddr_in serve;
    char buffer[BUFFER_SIZE] = {0};
    
    //##CAMADA DE TRANSPORTE
    
    if((soocket = socket(AF_INET, SOCK_STREAM, 0)) <0)
    {
        perror("Erro ao criar socket");
        return 1;
    };  
    
    serve.sin_family = AF_INET;
    serve.sin_port = htons(PORT);

    if(inet_pton(AF_INET, SERVE_IP, &serve.sin_addr) <= 0)
    {
        perror("Endereço invalido");
       return 1;
    }
    
    if(connect(soocket, (struct sockaddr *)&serve, sizeof(serve)) < 0)
    {
        perror("Falha na conexão");
        return 1;
    }

    printf("Conectado iniciando o Handshake\n");

    //##CAMANDA DE APLICAÇÃO
    unsigned char bytes_aleatorios[16];
    char chave_base64[25];
    
    gerar_bytes_aleatorios(bytes_aleatorios);
    base64_encode_16bytes(bytes_aleatorios, chave_base64);
    
    printf("[Cliente] Chave aleatória gerada para esta sessão: %s\n", chave_base64);    

    char handS[1024];
    sprintf(handS,    
            "GET / HTTP/1.1\r\n"
            "Host: %s:%d\r\n"
            "Upgrade: websocket\r\n"
            "Connection: Upgrade\r\n"
            "Sec-WebSocket-Key: %s\r\n"
            "Sec-WebSocket-Version: 13\r\n\r\n", SERVE_IP, PORT, chave_base64
            );
    write(soocket, handS, strlen(handS));
    
    read(soocket, buffer, BUFFER_SIZE);
    printf("%s\n", buffer);   

    if(strstr(buffer, "101 Switching Protocols") == NULL)
    {
        printf("[Cliente] Falha no Handshake do WebSocket. Resposta do servidor:\n%s\n", buffer);
        close(soocket);
        return -1;
    }
    int kill=  0x80;
    write(soocket, &kill, 1);


    sleep(2);

    close(soocket);
    printf("[Cliente] Conexao encerrada.\n");

    return 0;
}

void enviar_mensagem_ws(int fd, const char *texto)
{
    


}

void base64_encode_16bytes(const unsigned char *input, char *output) {
    int i = 0, j = 0;

    while (i < 15) {
        unsigned int triple = (input[i] << 16) + (input[i+1] << 8) + input[i+2];
        i += 3;
        output[j++] = b64_table[(triple >> 18) & 0x3F];
        output[j++] = b64_table[(triple >> 12) & 0x3F];
        output[j++] = b64_table[(triple >> 6) & 0x3F];
        output[j++] = b64_table[triple & 0x3F];
    }

    unsigned int triple = (input[i] << 16);
    output[j++] = b64_table[(triple >> 18) & 0x3F];
    output[j++] = b64_table[(triple >> 12) & 0x3F];
    output[j++] = '=';
    output[j++] = '=';
    output[j] = '\0';
}


void gerar_bytes_aleatorios(unsigned char *buffer) {
    for (int i = 0; i < 16; i++) {
        buffer[i] = rand() % 256; 
    }
}
