#include <stdlib.h>
#include <stdio.h>

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

TREE init(TREE tree){
    tree = malloc(sizeof(BinarySearchtree));
    tree->nodes = 0;
    tree->node = NULL;
    return tree;
};

struct no* insertNode(struct no *node, int value,int* count){
    if(node == NULL){
        node = malloc(sizeof(struct no));
        node->value = value;
        node->left = NULL;
        node->right = NULL;
        *count = *count + 1;
        return node;
    };
    if(value < node->value) node->left = insertNode(node->left, value, count);
    if(value > node->value) node->right = insertNode(node->right, value, count);
    return node;
}

void insert(TREE tree,int value){
    int new_cont = 0;
    tree->node = insertNode(tree->node,value,&new_cont);
    tree->nodes = tree->nodes + new_cont;
};

void inorderBFS(struct no *node){
    if(node->left != NULL) inorderBFS(node->left);
    printf("%d\n",node->value);
    if(node->right != NULL) inorderBFS(node->right);
    return;
};

void inorder(TREE tree){
    struct no *node = tree->node;
    inorderBFS(node);
};
void preorderBFS(struct no *node){
    if(node->left != NULL) preorderBFS(node->left);
    if(node->right != NULL) preorderBFS(node->right);
    printf("%d\n",node->value);
    return;
};

void preorder(TREE tree){
    struct no *node = tree->node;
    preorderBFS(node);
};

int BinarySearchBFS(struct no *node,int arg,int result){
    if(node->value == arg) return node->value;
    if(arg < node->value && node->left != NULL) result = BinarySearchBFS(node->left,arg,result);
    if(arg > node->value && node->right != NULL) result = BinarySearchBFS(node->right,arg,result);
    return result;
};

int BinarySearch(TREE tree, int arg){
    int result = 0;
    short int diff = result;
    result = BinarySearchBFS(tree->node, arg,result);
    if(result == diff) printf("nao esta\n");
    return result;
};
void freenode(struct no *node){
    if(node == NULL) return;
    freenode(node->left);
    freenode(node->right);
    free(node);
    printf("no limpo\n");
}

void freeTree(TREE tree){
    freenode(tree->node);
    free(tree);
    printf("arvore limpa\n");
};

struct no* removeNodeDfs(struct no *node, int arg){
    if(node->value == arg){
        if(node->left == NULL && node->right == NULL){
            node = NULL;
            free(node);
            printf("ok\n");
        };
        return node;
    };
    if(arg < node->value && node->left != NULL) node->left = removeNodeDfs(node->left,arg);
    if(arg > node->value && node->right != NULL) node->right = removeNodeDfs(node->right,arg);
    return node;
}

void removeNode(TREE tree, int arg){
   tree->node = removeNodeDfs(tree->node, arg);
};

int main(void){
    TREE tree;
    int a;
    tree = init(tree);
    insert(tree,2);
    insert(tree,5);
    insert(tree,10);
    insert(tree,1);
    removeNode(tree,1);
    inorder(tree);
    preorder(tree);
    a = BinarySearch(tree, 1);
    printf("%d, %d\n",tree->nodes,a);
    freeTree(tree);

    return 0;
};