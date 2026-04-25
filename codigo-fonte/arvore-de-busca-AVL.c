#include "arvore-de-busca-AVL.h"
#include <stdlib.h>
#include <stdio.h>



int FB(struct no* node){

    /*
        Calcula fator balanceamento, para rotacionar Arvore
    */

    if(node == NULL) return -1;
    return (heightDFS(node->left, 0)) - (heightDFS(node->right, 0));
}

struct no* balancear(struct no* node){

    /*
        Função principal que realiza 
        rotações com base no fator de balanceamento
    */

    if(node == NULL) return node;

    int fb = FB(node);

    if(fb < -1 && FB(node->right) <= 0) node = RSS(node);
    else if(fb > 1 && FB(node->left) >= 0) node = RSD(node);
    else if(fb > 1 && FB(node->left) < 0) node = RDD(node);
    else if(fb < -1 && FB(node->right) > 0) node = RDS(node);

    return node;
};

struct no* RSD(struct no* node){

    /*
        rotação para direita ----->
    */

    if(node == NULL || node->left == NULL) return node;

    struct no* noraiz = node->left;
    struct no* temp = noraiz->right;

    noraiz->right = node;
    node->left = temp;
    
    return noraiz;
}

struct no* RSS(struct no *node){
   
    /*
        rotação para a esquerda <--------
    */

    if(node == NULL || node->right == NULL) return node;
    struct no* noraiz = node->right;
    struct no* temp = noraiz->left;

    noraiz->left = node;
    node->right = temp;

    return noraiz;
}

struct no* RDS(struct no* node){

    /*
        Rotação para Direita-Esquerda <--------- ---------->    
    */

    node->right = RSD(node->right);
    return node = RSS(node);
}

struct no* RDD(struct no* node){

    /*
        Rotação para Esquerda-Direita
    */

    node->left = RSS(node->left);
    return node = RSD(node);
}