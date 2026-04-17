#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#include "arvore-base.h"
#include <stdbool.h>
#include <stdlib.h>

TREE init(TREE tree);
struct no* insertNode(struct no *node, int value,int* count);
bool insert(TREE tree,int value);
void inorderDFS(struct no *node);
void inorder(TREE tree);
void preorderDFS(struct no *node);
void preorder(TREE tree);
int BinarySearchBFS(struct no *node,int arg,int result);
int BinarySearch(TREE tree, int arg);
void freenode(struct no *node);
bool freeTree(TREE tree);
bool max(TREE tree);
bool min(TREE tree);
int _min(struct no *aux);
struct no* removeNodeDfs(struct no *node, int arg, TREE len);
bool removeNode(TREE tree, int arg);
int main(void);

#endif