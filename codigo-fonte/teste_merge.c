#include "merge_sort.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(void){
    int min = 1, max = 200;
    int teste[30];
    
    srand(time(NULL)); 
    for(int i = 0; i < (sizeof(teste)/4); i++) {
        // Gera numero entre 1 e 200
        int num = (rand() % (max - min + 1)) + min;
        teste[i]= num;
        
    }
    printf("--------------antes--------------\n");
    for(int i = 0; i < (sizeof(teste)/4); i++){
        printf("%d |", i);
    }
    printf("\n");
    for(int i = 0; i < ((sizeof(teste)/4) -2); i++){
        printf("--- ");
    }
    printf("\n");
     for(int i = 0; i < (sizeof(teste)/4); i++){
        printf("%d, ", teste[i]);
    }
    printf("\n");

    merge_sort(teste, 0, (sizeof(teste)/4)-1);

    printf("--------------depois--------------\n");
    for(int i = 0; i < (sizeof(teste)/4); i++){
        printf("%d |", i);
    }
    printf("\n");
    for(int i = 0; i < ((sizeof(teste)/4) -2); i++){
        printf("--- ");
    }
    printf("\n");
     for(int i = 0; i < (sizeof(teste)/4); i++){
        printf("%d, ", teste[i]);
    }
    printf("\n");

}