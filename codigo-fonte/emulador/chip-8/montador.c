#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef enum {
    INTEIRO,
    FLOAT,
    STRING,
    UINT16
}Types;

struct Node {
    void *data;
    Types type;
};

typedef struct 
{
    struct Node *no;
    int leght;
    int max;
}ArrayS;

const char hexadecimal[] = {'a','b','c','d','e','f'};

void freearray(ArrayS *array);
void list_type(ArrayS *array, Types type);
void *recuperar_dado(ArrayS *array, int index);
void montar_opcodes(ArrayS *array);
void add_data(ArrayS *array, Types type, void *data);

int main(int argc, char *argv[]){
    ArrayS array;
    memset(&array, 0, sizeof(ArrayS));
    
    if(argc != 2){ 
        printf("De uma entrada valida\n");
        return 0;
    } 
    char linha[200];
    memset(linha, 0, sizeof(linha));

    FILE *fd = fopen(argv[1], "r");
    while((fgets(linha, sizeof(linha), fd) != NULL)){
        linha[strcspn(linha, "\n")] = '\0';
        if((strstr(linha, ";")) == NULL){
            add_data(&array, STRING, linha);
        }
    }
    fclose(fd);
    for(int i = 0; i < array.leght; i++){
        if(array.no[i].type == STRING){
            char *resultado = recuperar_dado(&array, i);
            int size = strlen(resultado);
            uint16_t opcode = 0x0000;
            for(int a = 0; a < size; a++){
                char letra = tolower(resultado[a]);
                bool troca = true;
                uint16_t montar = 0x0000;
                for(int b = 0; b < sizeof(hexadecimal); b++){
                    if(letra == hexadecimal[b]){
                        montar = 0x0000;
                        montar = b + 10;
                        montar = montar << (((size - 1) - a) * 4);
                        opcode |= montar;
                        troca = false;
                        break;
                    }else{
                        continue;
                    }
                }
                if(troca && letra != ' ' && letra != '0'){ 
                    montar = 0;
                    montar = (int)(letra - '0');
                    montar = montar << (((size - 1) - a) * 4);
                    opcode |= montar;
                    troca = false;
            }
                
            }
            add_data(&array, UINT16, &opcode);
        }

    }
    printf("%i %i\n", array.max, array.leght);

    FILE *file = fopen("binario.ch8", "ab");
    for(int i = 0; i < array.leght; i++){
        if(array.no[i].type == STRING) printf("strings: %s\n", recuperar_dado(&array, i));
        if(array.no[i].type == UINT16){
            uint16_t dado = *(uint16_t *)(recuperar_dado(&array, i));
            printf("inteiro 16: %0x\n", dado);
            uint8_t dx = (dado & 0xFF00) >> 8;
            uint8_t dy = (dado & 0x00FF);
            fwrite(&dx, sizeof(uint8_t), 1, fd);
            fwrite(&dy, sizeof(uint8_t), 1, fd);
        }

    }
    fclose(file);


    
    freearray(&array);
    return 0;
}

void freearray(ArrayS *array){
    for(int i = 0; i < array->leght; i++){
        free(array->no[i].data);
    }
    free(array->no);
    return;
}

void add_data(ArrayS *array, Types type, void *data){
    if(array->no == NULL){
        array->max = 4;
        struct Node *newno = malloc(sizeof(struct Node) * array->max);
        if(newno == NULL) return;
        array->leght = 0;
        array->no = newno;
    }
    if(array->leght >= array->max){
        array->max *= 2;
        struct Node *temp = realloc(array->no, array->max *  sizeof(struct Node));
        if(temp == NULL) return;
        array->no = temp;
    }
    if(type == UINT16){
        uint16_t *inteiro = (uint16_t *)malloc(sizeof(uint16_t));
        if(inteiro == NULL) return;
        *inteiro = *(uint16_t *)data;
        array->no[array->leght].data = (void *)inteiro;
        array->no[array->leght].type = type;
    }else if(type == STRING){
        char *string = malloc(strlen((char *)data) + 1);
        if(string == NULL) return;
        strcpy(string, (char *)data);
        array->no[array->leght].data = (void *)string;
        array->no[array->leght].type = type;
    }else if(type == INTEIRO){
        int *inteiro = (int *)malloc(sizeof(int));
        if(inteiro == NULL) return;
        *inteiro = *(int *)data;
        array->no[array->leght].data = (void *)inteiro;
        array->no[array->leght].type = type;
    }
    array->leght++;
}

void *recuperar_dado(ArrayS *array, int index){
    if( index < 0 || index >= array->leght) return NULL;

    switch(array->no[index].type){
        case STRING:
            return (char *)array->no[index].data;
        case UINT16: 
            return (uint16_t *)array->no[index].data;
        case INTEIRO:
            return (int *)array->no[index].data;
        case FLOAT:
            return (float *)array->no[index].data;
        default:
            return array->no[index].data;
    }
}

void montar_opcodes(ArrayS *array){

    
    

}
