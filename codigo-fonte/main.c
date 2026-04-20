#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arvore-de-busca-AVL.h"

int main(void){
    
    TREE tree = NULL;
    int i, min = 1, max = 100;
    int teste[20];
    tree = init(tree);
    
    srand(time(NULL)); 
    for(i = 0; i < 20; i++) {
        // Gera numero entre 1 e 100
        int num = (rand() % (max - min + 1)) + min;
        teste[i]= num;
        insert(tree,num);
    }

    inorder(tree);
    printf("size = %d\n",height(tree));
    preorder(tree);
    for(int j = 0; j < 20; j++) printf("%d, ", teste[j]);
    printf("\n");
    //preorder(tree);
    //porlevel(tree);
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