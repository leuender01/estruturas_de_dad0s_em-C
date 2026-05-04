#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>
#include <pty.h>
#include <utmp.h>

extern char * environ[];

int main(void)
{

    int master;
    int slave;
    openpty(&master, &slave, NULL, NULL, NULL);

    pid_t pid = fork();
    if(pid == 0){
        login_tty(slave);
        char *PATH = "/usr/bin/bash";   

        char *argv[] = {PATH, NULL}; 
        execve(PATH, argv, environ);
    }else{
        printf("kellow world: %d\n", pid);
        getchar();
    }

    return 0;
}