#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <pthread.h>

#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUFFER_LEN (EVENT_SIZE + 16)

void *notificacao(void *arg);
volatile int num = 0;
int main(void)
{
    pthread_t id_thread;
    pthread_create(&id_thread, NULL, notificacao, NULL);
    while(1) printf("%i\r", num);
    return 0;
}

void *notificacao(void *arg)
{
    int *resultado = (int *)arg;
    int fd, wd;
    char buffer[BUFFER_LEN];
    printf("%ld, %ld\n",EVENT_SIZE,BUFFER_LEN);
        
    fd = inotify_init();
    if(fd < 0)
    {
        perror("Error ao inicializar inotify");
        close(fd);
        exit(EXIT_FAILURE);
    }


    wd = inotify_add_watch(fd, ".", IN_MODIFY);
    if(wd < 0)
    {
        perror("Error ao adicionar o observador");
        close(fd);
        exit(EXIT_FAILURE);
    }

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
            struct inotify_event *event = (struct inotify_event *) &buffer;
            if(event->len)
            {
                if(event->mask & IN_MODIFY)
                {
                    printf("Arquivo modificado: %s\n", event->name);
                    num++;
                }
            }
            i += EVENT_SIZE + event->len;
        }

    }
    
    inotify_rm_watch(fd,wd);
    close(fd);
    return NULL;
}
