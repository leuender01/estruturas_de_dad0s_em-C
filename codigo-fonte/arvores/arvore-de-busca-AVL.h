#ifndef BINARY_SEARCH_TREE_AVL
#define BINARY_SEARCH_TREE_AVL
#include "arvore-binaria-de-busca.h"// Precisa do codigo da arvore.

/*
    Arvore que se auto-balanceia vai
    ser inserido como uma extenção da 
    arvore binaria sendo dependente dela.
*/
int FB(struct no* node);//função que calcula o fator de balanceamento 
struct no* balancear(struct no* node);//função que balanceia uma vez
struct no* RSS(struct no* node);//função que rotaciona para esquerda
struct no* RSD(struct no *node);//função que rotaciona para direita
struct no* RDS(struct no* node);//função que rotaciona primerio para direita depois para esquerda
struct no* RDD(struct no* node);//função que rotaciona primeiro para esquerda depois para direita

#endif