#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arvore-de-busca-AVL.h"
#include <string.h>

int main(void){
    
    TREE tree = NULL;
    int min = 1, max = 1000;
    int testeAvl[102];
    int len = (sizeof(testeAvl)/4); 
    tree = init(tree);
    
    srand(time(NULL)); 
    for(int i = 0; i < len; i++) {
        int num = (rand() % (max - min + 1)) + min;
        testeAvl[i]= num;
        insert(tree, num);
    }
    

    printf("\n------------------testando a inserção---------------------\n");

    inorder(tree);
    preorder(tree);
    porlevel(tree);
    
    printf("fator balanceamneto %d\n" ,FB(tree->node));
    printf("tem o total de %d niveis\n", height(tree));
    printf("Quantidade de nos e = %d\n", tree->size);
    
    printf("\n------------------testando busca antes da remoção---------------------\n");
    for(int i = 0; i < 4; i++) {
        printf("buscar pelo numero %d esta %s\n", testeAvl[i], (BinarySearch(tree,testeAvl[i]))? "TRUE" : "FALSE");
    }
    
    
    printf("\n------------------testando a remoção---------------------\n");
    removeNode(tree, testeAvl[0]);    
    removeNode(tree, testeAvl[1]);    
    removeNode(tree, testeAvl[2]);    

    inorder(tree);
    preorder(tree);
    porlevel(tree);
     
    printf("fator balanceamneto %d\n" ,FB(tree->node));
    printf("tem o total de %d niveis\n", height(tree));
    printf("Quantidade de nos e = %d\n", tree->size);

    printf("\n------------------testando busca depois da remoção---------------------\n");
    for(int i = 0; i < 4; i++) {
        printf("buscar pelo numero %d esta %s\n", testeAvl[i], (BinarySearch(tree,testeAvl[i]))? "TRUE" : "FALSE");
    }
    

    freeTree(tree);
    return 0;
}