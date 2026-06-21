#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


void scan(int port);
int* definerange(char *cha);

int main(int argc, char *argv[])
{
    int *range;
    if(argc == 1) 
    {
        printf("digite um formato conpativel\n");
        return 0;
    }
    
    for(int i = 1; i < argc ; i++)
    {
        
        range = definerange(argv[i]);
        if(range[1] == -1) scan(range[0]);
        else
        {
            int ordem = range[0] - range[1];
            if(ordem > 0) for(int i = range[1]; i <= range[0]; i++) scan(i);
            else if(ordem < 0) for(int i = range[0]; i <= range[1]; i++) scan(i);
            else scan(range[0]);
        }
    }
    return 0;
}

int* definerange(char *cha)
{
    int index = 0;
    static int range[2] = {0};
    if(strlen(cha) > 2)
    {
        int8_t separador = 0;
        for(int i = 0; i < strlen(cha); i++)
        {
            if(cha[i] == '-'){
                index = i;
                separador++;
            }

        }
        if(separador == 0)
        {
            range[0] = atoi(cha);
            range[1] = -1;
            return range;
        }else{
            int len = (strlen(cha) - index) + 1, j = 0;
            range[0] = atoi(cha);
            char new[len];
            for(int i = index + 1; i < strlen(cha); i++)
            {
                new[j] = cha[i];
                j++;
            }
            new[len  - 1] = '\0';
            range[1] = atoi(new);
            return range;
        }


    }else
    {
        range[0] = atoi(cha);
        range[1] = -1;
    }
    return range;
}


void scan(int port)
{

    int socket_fd;
    struct sockaddr_in myserve;
    
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    myserve.sin_family = AF_INET;
    myserve.sin_port = htons(port);
    myserve.sin_addr.s_addr = INADDR_ANY;
            
    if(bind(socket_fd, (struct sockaddr*)&myserve, sizeof(myserve)) != 0)
    {
        printf("a porta %i esta oculpada\n", port) ;
        close(socket_fd);
        return;
    }
    
    printf("a porta %i esta livre\n", port);
    close(socket_fd);
    return;
}
