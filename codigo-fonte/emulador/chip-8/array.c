#include "array.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

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
