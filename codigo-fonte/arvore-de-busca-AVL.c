#include "arvore-de-busca-AVL.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void rotate(TREE tree){
    struct no *node= tree->node;
    int left = heightDFS(node->left, 0), right = heightDFS(node->right, 0), diff;
    diff = left - right;
    printf("diferença = %d", diff); 
}

