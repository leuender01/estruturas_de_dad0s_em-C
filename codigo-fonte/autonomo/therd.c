#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

int a = -1;

void *for_infinite(void *arg){

    int *var = (int *)arg;
    while(*var  < 1){
        printf("%d\n", *var);

    }
    int *c = malloc(sizeof(int));
    if(c != 0) *c = 20;
    
    return (void *)c;


}
pthread_t threads[2];
pthread_mutex_t mutex;


int main(void){
    void *resultado;
    
    pthread_create(&(threads[0]), NULL, for_infinite, &a);
    while(1){
        sleep(1);
        if(a > 1) break;
        a += 1;
    }

    pthread_join(threads[0], &resultado);
    
    int *convert = (int *)resultado;
    printf("%d\n", *convert);













    /*
    clock_t inicio = clock();
    time_t tempo;
    struct tm *tempo_atual;
    tempo = time(NULL);

    tempo_atual = localtime(&tempo);

    
    for(int i = 0; i < 3; i++){
        printf("%d/%d/%d\n", tempo_atual->tm_mday,tempo_atual->tm_mon,tempo_atual->tm_year + 1900);
    }

    clock_t fim = clock();
    double tempo_gasto = (double)(fim - inicio) /  CLOCKS_PER_SEC;
    printf("%f\n", tempo_gasto);
    */
    return 0;
}

