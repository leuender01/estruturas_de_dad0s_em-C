#ifndef HASH_H
#define HASH_H

#define TAM_TABLE_HASH 100 

struct node{
    char *key;
    char *value;
    struct node *colision;  
};

typedef struct{
    struct node *array[TAM_TABLE_HASH];   
}HASH;



#endif