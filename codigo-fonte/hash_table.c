#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

int len(Hash tab){
    int size= 0;
    for(int i = 0; i<TAM_MAX; i++){
        if(tab[i] == NULL){
          size++;  
        };
    };
    return size;
};
void init(Hash tab){
    for(int i=0;i<TAM_MAX;i++) tab[i] = NULL;
};

void insert(Hash tab, int num){
    int en = len(tab);
    if((en - TAM_MAX) == TAM_MAX) return;
    Dados* aux = (Dados*)malloc(sizeof(Dados));
    aux->info = num;
    tab[TAM_MAX-en] = aux;
};
void printHash(Hash tab){
    int i= 0;
    while(tab[i] != NULL){
        printf(" ______________________\n| indice: %d | valor: %d |\n",i,tab[i]->info);
        i++;
    };
    printf(" ______________________\n");
};
void removeHash(Hash table, int indice){
    if(indice > (TAM_MAX -1) || indice < 0) return;
    while (indice<TAM_MAX && table[indice] != NULL)
    {
        table[indice] = table[indice+1];
        indice++;
    };
    table[TAM_MAX- 1] = NULL;
};
int gethash(Hash tab, int indice){
    if(indice > (TAM_MAX - 1) || indice < 0) return 0;
    return tab[indice]->info;
};
void freeHash(Hash tab){
    int i =0;
    while(tab[i] != NULL){
        free(tab[i]);
        printf("%d\n", i);
        i++;
    };
}