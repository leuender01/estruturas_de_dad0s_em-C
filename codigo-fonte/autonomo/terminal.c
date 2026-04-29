#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>

int main(void)
{

    int fd[2];
    char buffer[30];
    char *enviar[] = {"ola mundo\n", "adeus mundo\n"};
    pipe(fd);

    pid_t pid = fork();
    if (pid == 0)
    {

        int k = 0;
        while (true){
            close(fd[0]); // fecha a leitura
            if(k > 1) k = 0;
            write(fd[1], enviar[k], strlen(enviar[k]));
            k++;
            sleep(1);
        };
    }
    else
    {
        while (true)
        {   
            close(fd[1]);                        // fecha a escrita
            read(fd[0], buffer, sizeof(buffer)); // inicia a leitura

            FILE *fille = fopen("leu", "a");
            fprintf(fille, "%s", buffer);
            fclose(fille);
            sleep(1);
        }
    }

    return 0;
}