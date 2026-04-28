#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"

int calcularHash(char *string);

int main(void){
    HASH table;
    
    return 0;
}


int calcularHash(char *string){
    int calc;
    for(int i = 0; i < strlen(string); i++){
        calc = calc + *(string + i);
        calc = calc << 1;
    }
    return calc % TAM_TABLE_HASH;
}


