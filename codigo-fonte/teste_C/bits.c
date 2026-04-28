#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *arquivo;
    int num[] = {0b101,0b11,0b1101}, num_lido, conta;
    char letra[] ="ADD reax", letrA[15];
    
    /*
    arquivo = fopen("teste.bin", "rb");
    fseek(arquivo, 0, SEEK_SET);
    if(arquivo == NULL){
        return 1;
    };

    conta = fread(letrA, sizeof(char),99,arquivo);
    letrA[conta-1] = '\0';
    fclose(arquivo);
    printf("%s\n %0x, %ld\n", letrA, conta, sizeof(letra));
    */


    
    arquivo = fopen("teste.bin", "wb");
    fseek(arquivo, 0, SEEK_SET);
    if(arquivo == NULL){
        puts("nao conseguimos achar\n");
        return 1;
    };
    fwrite(&letra,sizeof(letra), 1, arquivo);
    fclose(arquivo);
    printf("%ld %0x", sizeof(letra), 0b1010);
    
    
    return 0;
};
