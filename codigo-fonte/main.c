#include <stdio.h>
#include <stdlib.h>
#include "arvore-de-busca-AVL.h"

int main(void){
    TREE tree;
    int a;
    tree = init(tree);
    insert(tree,2);
    insert(tree,5);
    insert(tree,4);
    insert(tree,10);
    insert(tree,1);
    insert(tree,0);
    //max(tree);
    //min(tree);
    inorder(tree);
    preorder(tree);
    removeNode(tree, 5);
    inorder(tree);
    preorder(tree);
    /*//inorder(tree);
    a = BinarySearch(tree, 1);
    //preorder(tree);
    printf("%d, %d\n",tree->nodes,a);
    */
    freeTree(tree);

    return 0;
}