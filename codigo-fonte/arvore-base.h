#ifndef ARVORE_H
#define ARVORE_H

#include <stdlib.h>

struct no{
    int value;
    struct no *left;
    struct no *right;
};

struct ArvoreBinariaBusca{
    int nodes;
    struct no *node;
};

typedef struct ArvoreBinariaBusca BinarySearchtree;
typedef BinarySearchtree* TREE;


#endif