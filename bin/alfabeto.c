#include <stdio.h>
#include <stdlib.h>

#define MAISCULO 65
#define MINUSCULO 97

char* Alfabeto(int letra){
    if(letra > 26 || letra < 0) return NULL;
    char *alfabeto = malloc(sizeof(char)*(letra+1));
    *(alfabeto + letra) = '\0';
    letra = letra + MINUSCULO;
    char aux = MINUSCULO;
    for(int i = 0;(i+MINUSCULO) < letra;i++){
        printf("%c\n",aux);
        alfabeto[i]= aux;  
        aux = aux + 1;
    };
    return alfabeto;
};


int main(void){
    
    char *alfabeto = Alfabeto(26);

    /*char alfabeto = MINUSCULO;
    while (alfabeto < (MINUSCULO+26))
    { 
        alfabeto = alfabeto + 1;
        };
        */
       printf("%s",alfabeto);
       //printf("%c\n",MINUSCULO);
    free(alfabeto);
    return 0;

};