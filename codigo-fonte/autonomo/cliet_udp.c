#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr;

    // 1. Criar o socket UDP
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Falha na criação do socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY; // Mude para o IP do servidor se for remoto

    // 2. Enviar mensagem ao servidor
    const char *message = "Olá, Servidor!";
    sendto(sockfd, message, strlen(message), 0, (const struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("Mensagem enviada ao servidor.\n");

    // 3. Aguardar resposta do servidor (opcional)
    socklen_t addr_len = sizeof(server_addr);
    int len = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, 0, (struct sockaddr *)&server_addr, &addr_len);
    buffer[len] = '\0';
    printf("Resposta do servidor: %s\n", buffer);

    close(sockfd);
    return 0;
}

