#ifndef ARVORE_RUMBRO_NEGRA
#define ARVORE_RUMBRO_NEGRA

#include <stdlib.h>
#include <stdbool.h>

typedef enum {BLACK, RED} Color;

struct node{
    int value;
    Color color;
    struct node *left, *right, *father;
};

typedef struct node* NODE;

int heigth(NODE tree, int len);
void insertNode(NODE *node, int value);
void inorder(NODE node);
void preorder(NODE node);
bool BinarySearch(NODE node,int arg);
void freenode(NODE node);
bool max(NODE tree);
bool min(NODE tree);
void porlevel(NODE tree);
struct node * newNode(int value, NODE* father, struct node* left, struct node* right);
void _insertNode(NODE *node, int value, NODE father);
void caminho(NODE *node);

#endif