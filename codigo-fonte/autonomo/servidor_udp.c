#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <arpa/inet.h> 
#include <sys/socket.h> 
#include <string.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    int socket_fd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);


    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Falha na criação do socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 2. Associar o socket à porta e endereço
    if (bind(socket_fd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Falha no bind");
        exit(EXIT_FAILURE);
    }

    printf("Servidor UDP aguardando pacotes na porta %d...\n", PORT);

    // 3. Receber dados do cliente
    int len = recvfrom(socket_fd, (char *)buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
    buffer[len] = '\0';
    printf("Mensagem recebida: %s\n", buffer);

    // 4. Enviar resposta de volta
    const char *response = "Mensagem recebida com sucesso!";
    sendto(socket_fd, response, strlen(response), 0, (const struct sockaddr *)&client_addr, addr_len);
    printf("Resposta enviada.\n");

    close(socket_fd);

    return 0;
}

