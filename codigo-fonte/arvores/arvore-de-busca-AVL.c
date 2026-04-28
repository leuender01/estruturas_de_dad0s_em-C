#include "arvore-de-busca-AVL.h"
#include <stdlib.h>
#include <stdio.h>



int FB(NODE node){

    /*
        Calcula fator balanceamento, para rotacionar Arvore
    */

    if(node == NULL) return -1;
    return (height(node->left, 0)) - (height(node->right, 0));
}

NODE balancear(NODE node){

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

NODE RSD(NODE node){

    /*
        rotação para direita ----->
    */

    if(node == NULL || node->left == NULL) return node;

    NODE noraiz = node->left;
    NODE temp = noraiz->right;

    noraiz->right = node;
    node->left = temp;
    
    return noraiz;
}

NODE RSS(NODE node){
   
    /*
        rotação para a esquerda <--------
    */

    if(node == NULL || node->right == NULL) return node;
    NODE noraiz = node->right;
    NODE temp = noraiz->left;

    noraiz->left = node;
    node->right = temp;

    return noraiz;
}

NODE RDS(NODE node){

    /*
        Rotação para Direita-Esquerda <--------- ---------->    
    */

    node->right = RSD(node->right);
    return node = RSS(node);
}

NODE RDD(NODE node){

    /*
        Rotação para Esquerda-Direita
    */

    node->left = RSS(node->left);
    return node = RSD(node);
}