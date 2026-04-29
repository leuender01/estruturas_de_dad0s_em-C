#ifndef BINARY_SEARCH_TREE_AVL
#define BINARY_SEARCH_TREE_AVL
#include "arvore-binaria-de-busca.h"// Precisa do codigo da arvore.

/*
    Arvore que se auto-balanceia vai
    ser inserido como uma extenção da 
    arvore binaria sendo dependente dela.
*/
int FB(NODE node);//função que calcula o fator de balanceamento 
NODE balancear(NODE node);//função que balanceia uma vez
void updateheigth(NODE node);// função que atualiza a altura de um nó

NODE RSS(NODE node);//função que rotaciona para esquerda
NODE RSD(NODE node);//função que rotaciona para direita
NODE RDS(NODE node);//função que rotaciona primerio para direita depois para esquerda
NODE RDD(NODE node);//função que rotaciona primeiro para esquerda depois para direita

#endif