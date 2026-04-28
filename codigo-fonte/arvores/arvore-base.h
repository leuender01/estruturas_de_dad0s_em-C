#ifndef ARVORE_H
#define ARVORE_H

/*
    Não e a melhor estruta mais foi a que eu achei melhor usar. Pode ser melhorada!
*/

//------------Estrututa_Basica_Para_Uma_Arvore_Binaria-----------

struct no{//estrutura do no
    int value;//valor do Nó em si (nao precisa ser um número)
    struct no *left;// ponteiro para o nó a esquerda
    struct no *right;// ponteiro para o nó a direita
};

struct ArvoreBinariaBusca{// Estrutura da Arvore em sí
    int size;// armazena a quantidade de nos a ser inseria
    struct no *node;// ponteiro para os nós em si
};

typedef struct ArvoreBinariaBusca BinarySearchtree; //trocando as definições por motivos: porque eu quis
typedef BinarySearchtree* TREE;

#endif