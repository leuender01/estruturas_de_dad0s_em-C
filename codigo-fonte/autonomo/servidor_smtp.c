#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <openssl/ssl.h>

#define PORT 587
#define SERVER_HOST "smtp.gmail.com"

char *lerchave(void);

int main(void){
    int socket_fd;
    struct sockaddr_in myserve;
    char input[1024];
    char *hello = "EHLO servidor_smtp\r\n";
    char *teste = lerchave();
    if(teste == NULL)
    {   
        printf("Arquivo com nome \"key\" nao existem ou esta vazio");
        return 0;
    }
    printf("%s", teste);
 
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        
    if(socket_fd > 0) printf("Socket aberto\n"); 
    else{
        perror("erro ao abrir socket");
        return 0;
    } 
    struct hostent *host = gethostbyname(SERVER_HOST);
    
    printf("%s\n%i\n%i\n%s\n",host->h_name,host->h_addrtype,host->h_length, host->h_addr);

    myserve.sin_family = AF_INET;
    myserve.sin_port = htons(PORT);
    memcpy(&myserve.sin_addr, host->h_addr, host->h_length);
    //myserve.sin_addr.s_addr = INADDR_ANY;

    printf("tentando abrira porta %i\n",PORT); 
            
    if(connect(socket_fd, (struct sockaddr*)&myserve, sizeof(myserve)) != 0)
    {
        printf("Erro ao connectar.\n");
        return 0;
    }

    ssize_t bytes_lidos = read(socket_fd, input, sizeof(input));
    input[bytes_lidos] = '\0';
    printf("mensagem da saudações %s , %li\n", input, bytes_lidos);

    write(socket_fd, hello, strlen(hello));

    memset(input, 0, sizeof(input));
    bytes_lidos = read(socket_fd, input, sizeof(input) - 1);
    input[bytes_lidos] = '\0';
    printf("Resposta do EHLO:\n%s , %li\n", input, bytes_lidos);

    char *startls = "STARTTLS\r\n";
    write(socket_fd, startls, strlen(startls));

    memset(input, 0, sizeof(input));
    bytes_lidos = read(socket_fd, input, sizeof(input) - 1); 
    input[bytes_lidos] = '\0';
    printf("%s , %li\n", input, bytes_lidos);
    
    if(strncmp(input, "220", 3) == 0)
    {
        printf("Inicioando Criptografia TLS\n");
        SSL_library_init();
        OpenSSL_add_all_algorithms();
        SSL_load_error_strings();
        
        const SSL_METHOD *method = TLS_client_method();
        SSL_CTX *ctx = SSL_CTX_new(method);
        if(!ctx)
        {
            perror("Erro ao criar contexto SSL");
            close(socket_fd);
            return 0;
        }

        SSL *ssl = SSL_new(ctx);
        SSL_set_fd(ssl, socket_fd);

        if (SSL_connect(ssl) <= 0) {
            perror("Erro no handshake TLS");
            SSL_free(ssl);
            SSL_CTX_free(ctx);
            close(socket_fd);
            return 0;
        }

        printf("conexão TLS stabelecido com sucesso\n");
        SSL_write(ssl, hello, strlen(hello));
        memset(&input, 0, sizeof(input));
        SSL_read(ssl, input, sizeof(input) - 1);
        printf("%s\n", input);
        

        SSL_write(ssl, "AUTH PLAIN\r\n", 12);
        memset(&input, 0, sizeof(input));
        SSL_read(ssl, input, sizeof(input) - 1);
        printf("Resposta AUTH:%s\n", input);

        
        SSL_write(ssl, teste, strlen(teste));
        memset(&input, 0, sizeof(input));
        SSL_read(ssl, input, sizeof(input) - 1);
        printf("%s\n", input);
        
        char *email = "MAIL FROM:<email-remetente>\r\n";//email do remetente
        SSL_write(ssl, email, strlen(email));
        memset(&input, 0, sizeof(input));
        SSL_read(ssl, input, sizeof(input) - 1);
        printf("%s\n", input);

        char *email_dest = "RCPT TO:<email-destinatario>\r\n"; //email do destinatario
        SSL_write(ssl, email_dest, strlen(email_dest));
        memset(&input, 0, sizeof(input));
        SSL_read(ssl, input, sizeof(input) - 1);
        printf("%s\n", input);

        SSL_write(ssl,"DATA\r\n", 6); 
        memset(&input, 0, sizeof(input));
        SSL_read(ssl, input, sizeof(input) - 1);
        printf("%s\n", input);
        
        char *email_conteudo = 
            "From: <email-remetente>\r\n"
            "To: <email destinatario>\r\n"
            "Subjetct: Teste de Socket em C\r\n"    
            "Content-Type: text/plain; charset=UTF-8\r\n" 
            "\r\n"
            "Mensagem enviada com sucesso utilizando sockets em C\r\n" //mensagem em si
            ".\r\n";

        SSL_write(ssl,email_conteudo, strlen(email_conteudo)); 
        memset(&input, 0, sizeof(input));
        SSL_read(ssl, input, sizeof(input) - 1);
        printf("%s\n", input);
    
        SSL_write(ssl, "QUIT\r\n", 6);

        SSL_shutdown(ssl);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
    }else{
        
        perror("Erro ao conectar"); 
    }
    free(teste);
    /*
   

    */



    /*
    char ip_client[INET_ADDRSTRLEN];
    inet_ntop( AF_INET, &(client.sin_addr), ip_client, INET_ADDRSTRLEN );
    printf("IP que enviou: %s\n", ip_client);
    printf("Enviando mensagem de retorno\n");

    close(connection_fd);
    */
    
    close(socket_fd);

    return 0;
}

char *lerchave(void)
{
    FILE *fd = fopen("key","rb");//procura pelo arquivo com nome key
    if(fd == NULL) return NULL;
    size_t bytes_lidos = 0;
    char *conteudo;
    int len = 0;
    char buffer;
    
    while((bytes_lidos = fread(&buffer, 1, 1,fd)) > 0) len++;
    
    rewind(fd);
    conteudo = malloc((len * sizeof(char) ) + 3);
     
    if(conteudo == NULL)
    {
        fclose(fd);
        return NULL;
    }

    fread(conteudo, sizeof(char), len, fd);
    strcat(conteudo, "\r\n");
    conteudo[len + 2]  = '\0';
    
    fclose(fd);
    return conteudo;
}
