#ifndef ARVORE_H
#define ARVORE_H

/*
    Não e a melhor estruta mais foi a que eu achei melhor usar. Pode ser melhorada!
*/

//------------Estrututa_Basica_Para_Uma_Arvore_Binaria-----------

struct no{//estrutura do no
    int value;//valor do Nó em si (nao precisa ser um número)
    int height;
    struct no *left;// ponteiro para o nó a esquerda
    struct no *right;// ponteiro para o nó a direita
};

typedef struct no* NODE;

#endif