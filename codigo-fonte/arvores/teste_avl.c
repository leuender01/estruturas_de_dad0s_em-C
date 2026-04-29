#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arvore-de-busca-AVL.h"
#include <string.h>

int main(void){
     
    NODE tree = NULL;

    int min = 2, max = 1230;
    int testeAvl[10];
    int len = (sizeof(testeAvl)/4) -1 ; 

    srand(time(NULL)); 
    for(int i = 0; i < len; i++) {
        int num = (rand() % max) + min;
        testeAvl[i]= num;
        printf("rendom %d\n",testeAvl[i]);
        tree = insertNode(tree, num);
    }
    printf("\n------------------testando a travessia---------------------\n");
    inorder(tree);
    printf("\n");
    preorder(tree); 
    printf("\n");
    porlevel(tree);
    printf("\n");

    printf("\n------------------testando a inserção---------------------\n");
    
    printf("fator balanceamneto %d\n",FB(tree));
    printf("tem o total de niveis %d\n", height(tree, 0));
    printf("Quantidade de nos e = %d\n", tree->height);
    
    printf("\n------------------testando busca antes da remoção---------------------\n");
    for(int i = 0; i < len; i++) {
        printf("buscar pelo numero %d esta %s\n", testeAvl[i], (BinarySearch(tree,testeAvl[i]))? "TRUE" : "FALSE");
    }
    
    
    printf("\n------------------testando a remoção---------------------\n");
    removeNode(&tree, testeAvl[0]);    
    removeNode(&tree, testeAvl[1]);    
    removeNode(&tree, testeAvl[2]);    
    removeNode(&tree, testeAvl[3]);    
    removeNode(&tree, testeAvl[4]);    

    inorder(tree);
    printf("\n");
    preorder(tree);
    printf("\n");
    porlevel(tree);
    printf("\n");
     
    printf("fator balanceamneto %d\n" ,FB(tree));
    printf("tem o total de %d niveis\n", height(tree, 0));
    printf("Quantidade de nos e = %d\n", tree->height);

    printf("\n------------------testando busca depois da remoção---------------------\n");
    for(int i = 0; i < len; i++) {
        printf("buscar pelo numero %d esta %s\n", testeAvl[i], (BinarySearch(tree,testeAvl[i]))? "TRUE" : "FALSE");
    }
    

    freenode(tree);
    return 0;
}