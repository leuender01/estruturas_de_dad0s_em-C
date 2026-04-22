#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arvore-de-busca-AVL.h"

int main(void){
    
    TREE tree = NULL;
    //int i, min = 1, max = 100;
    //int teste[20];
    int testeAvl[7] = {1,2,3,4,5,6,7};
    int testeAvl2[7] = {4,3,2,1,5,6,7};
    int testeAvl3[5] = {5,4,3,2,1};
    tree = init(tree);
    
    srand(time(NULL)); 
    for(int i = 0; i < 7; i++) {
        // Gera numero entre 1 e 100
        //int num = (rand() % (max - min + 1)) + min;
        //teste[i]= num;
        insert(tree,i);
    }

    inorder(tree);
    preorder(tree);
    porlevel(tree);
    printf("\n");
    printf("altura e igual a %d\n", height(tree));
    rotate(tree);
    rotate(tree);
    rotate(tree);
    printf("altura e igual a %d\n", height(tree));
    printf("\n");
    inorder(tree);
    preorder(tree);
    porlevel(tree);
    printf("fator balanceamneto %d" ,FB(tree->node));
    //printf("size = %d\n",height(tree));
    //for(int j = 0; j < 20; j++) printf("%d, ", teste[j]);
    //preorder(tree);
    /*
    insert(tree,2);
    insert(tree,5);
    insert(tree,4);
    insert(tree,10);
    insert(tree,1);
    insert(tree,0);
    //max(tree);
    //min(tree);
    removeNode(tree, 5);
    inorder(tree);
    inorder(tree);
    a = BinarySearch(tree, 1);
    //preorder(tree);
    printf("%d, %d\n",tree->nodes,a);
    */ 
    freeTree(tree);

    return 0;
}