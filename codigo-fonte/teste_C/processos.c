#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
    pid_t pid; //declara uma varialve especial chamada pid_t
    pid = fork();//parte que separa o preoccessamento
    char *const argv[] = {"/bin/echo","ola"}; //array de execução especificamente em terminal linux bash

    if(pid == 0){

        printf("filho %d\n",getpid());//pega o pid atual
        execv("/bin/echo",argv);//executa o cmd

    }
    
    waitpid(pid,NULL,0); // espera processo terminar
    printf("pid atual: %d\n", getpid()); //pega o pid atual
    getchar();//capricho de minha parte

    return 0;
}