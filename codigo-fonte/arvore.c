#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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

bool insert(TREE tree,int value){
    int new_cont = 0;
    tree->node = insertNode(tree->node,value,&new_cont);
    if(new_cont != 0){
        tree->nodes = tree->nodes + new_cont;
        return true;
    }
    return false;
};

void inorderDFS(struct no *node){
    if(node->left != NULL) inorderDFS(node->left);
    printf(", %d",node->value);
    if(node->right != NULL) inorderDFS(node->right);
    return;
};

void inorder(TREE tree){
    struct no *node = tree->node;
    printf("inorder>>");
    inorderDFS(node);
    printf("\n");
};
void preorderDFS(struct no *node){
    printf(", %d",node->value);
    if(node->left != NULL) preorderDFS(node->left);
    if(node->right != NULL) preorderDFS(node->right);
    return;
};

void preorder(TREE tree){
    struct no *node = tree->node;
    printf("preorder>>");
    preorderDFS(node);
    printf("\n");
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
    return;
}

bool freeTree(TREE tree){
    freenode(tree->node);
    free(tree);
    printf("arvore limpa\n");
    return true;
};

bool max(TREE tree){
    if(tree == NULL) return false;
    struct no *aux = tree->node;
    while(aux->right != NULL) aux = aux->right;
    if(aux == NULL) return false;
    printf("%d\n", aux->value);    
    return true;    
}

bool min(TREE tree){
    if(tree == NULL) return false;
    struct no *aux = tree->node;
    while(aux->left != NULL) aux = aux->left;
    if(aux == NULL) return false;
    printf("%d\n", aux->value);    
    return true;    
}
int _min(struct no *aux){
    if(aux == NULL) return -1;
    while(aux->left != NULL) aux = aux->left;   
    return aux->value;    
}

struct no* removeNodeDfs(struct no *node, int arg, TREE len){
    if(node == NULL) return NULL;
    if(arg < node->value && node->left != NULL){
        node->left = removeNodeDfs(node->left,arg,len);
    }else if(arg > node->value && node->right != NULL){
        node->right = removeNodeDfs(node->right,arg,len);
    }else if(node->value == arg){
        if(node->left == NULL){
            struct no *temp = node->right;
            free(node);
            len->nodes--;
            return temp;
        }else if(node->right == NULL){
            struct no *temp = node->left;
            free(node);
            len->nodes--;
            return temp;
        }else{
            int aux = _min(node->right);
            if(aux == -1) return node;
            node->value = aux;
            node->right = removeNodeDfs(node->right, aux,len);    
        };
    };
    return node;
}

bool removeNode(TREE tree, int arg){
    int old_size = tree->nodes;
    tree->node = removeNodeDfs(tree->node, arg,tree);
    return !(tree->nodes == old_size);
};

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
};

