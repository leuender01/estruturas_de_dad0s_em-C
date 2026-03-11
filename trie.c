#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct aresta {
    struct aresta *prox;
    struct node *node;
};

struct node{
    struct aresta *prox;
    char cha;
    char fim;
};

typedef struct node NODE;
typedef NODE* trie;

trie init(trie tree){
    NODE *aux = malloc(sizeof(NODE));
    aux->cha=0;
    aux->prox = NULL;
    aux->fim = 1;
    return aux;
    
};

void limpar_mem(trie tree){
    if(tree->prox != NULL){
        limpar_mem(tree->prox->node);
        free(tree->prox);
    };
    free(tree);
    printf("ok\n");
    return;
};
trie insert_tree(trie tree , char *cha, int len){
        if(tree->cha == 0 && len>0){
            //printf("%c , %d\n",*cha,len);
            struct aresta *Aresta = malloc(sizeof(struct aresta));
            NODE *node = malloc(sizeof(struct node));
            node->cha = *cha;
            len == 0  ? node->fim = 1 : node->fim = 0;
            Aresta->prox = NULL;
            Aresta->node = insert_tree(tree, cha + 1,(len -1));
            node->prox = Aresta;
            return node;
        };
    return tree;  
};

trie tree_insert(trie tree, char cha[]){
    tree = insert_tree(tree, cha, strlen(cha));
    //printf("%c\n",tree->prox->node->prox->node->cha);
    return tree;
};

void tree_print(trie tree){
    trie aux = tree;
    while(aux->prox != NULL){
        printf("%c , %d ",aux->cha, aux->fim);
        aux = aux->prox->node;
    };
    printf("\n");
};

int main(){
    trie arvore;
    arvore = init(arvore);
    printf("%c\n",'a');
    arvore = tree_insert(arvore,"leuender");
    tree_print(arvore);
    limpar_mem(arvore);
};