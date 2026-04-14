#ifndef HASH_H

#define HASH_H
#define TAM_MAX 50

struct dates{ int info;};
typedef struct dates Dados;
typedef Dados* Hash[TAM_MAX];

int len(Hash tab);//tamanho da tabela
void init(Hash tab);//inicializar tabela
void insert(Hash tab, int num);//inserir na tabela
void printHash(Hash tab);//exibir tabela
void removeHash(Hash table, int indice);//remover 1 elemento da tabela
int gethash(Hash tab, int indice);//pegar um valor pelo indice
void freeHash(Hash tab);//liberar memoria

#endif