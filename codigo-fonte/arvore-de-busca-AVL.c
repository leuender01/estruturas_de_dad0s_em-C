#include "arvore-de-busca-AVL.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>


int FB(struct no* node){
    if(node == NULL) return 0;
    return (heightDFS(node->left, 0) - 1) - (heightDFS(node->right, 0) - 1);
}

void rotate(TREE tree){
    /*
        Função que fica em loop ate balancear a arvore por completo
    */

    struct no *node= tree->node;
    int fb = FB(node); 
    while(fb > 1 || fb < -1){
        node = balancear(node);
        fb = FB(node);
    };
    tree->node = node;
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

//rotação para direota ----->
struct no* RSD(struct no* node){
    if(node == NULL) return node;

    struct no* temp = node;
    node = node->left;
    temp->left =  NULL;
    node->right = temp;
    
    return node;
}

//rotação para esquerda <-------
struct no* RSS(struct no *node){
    if(node == NULL) return node;

    struct no* temp = node;
    node = node->right;
    temp->right = NULL;
    node->left = temp;
    
    return node;
}
//rotação Direita-Esquerda <-------- ------>
struct no* RDS(struct no* node){
    node->right = RSD(node->right);
    return node = RSS(node);
}

//rotação Esqeuerda-Direita ---------> <--------
struct no* RDD(struct no* node){
    node->left = RSS(node->left);
    return node = RSD(node);
}