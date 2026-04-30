#include <stdlib.h>
#include <stdio.h>
#include "arvore_rumbro_negra.h"
#include <inttypes.h>
#include <stdbool.h>
#include "Queue_negra.h"

int main(void)
{
    NODE tree = NULL;
    insertNode(&tree, 2);
    insertNode(&tree, 1);
    insertNode(&tree, 5);
    insertNode(&tree, 10);
    insertNode(&tree, 547);
    insertNode(&tree, 132);
    insertNode(&tree, 91);
    insertNode(&tree, 3);
    insertNode(&tree, 21);
    insertNode(&tree, 12);
    printf("numero foi %s\n", BinarySearch(tree, 0) ? "TRUE": "FALSE");
    inorder(tree);
    printf("\n");
    preorder(tree);
    printf("\n");
    min(tree);
    max(tree);
    porlevel(tree);

    printf("os niveis e igual %d \n",heigth(tree, 0));
    return 0;
}

void insertNode(NODE *node, int value)
{
    _insertNode(node, value, NULL);
    
}

void _insertNode(NODE *node, int value, NODE father){
    if(*node == NULL){
        
        *node = newNode(value, &father, NULL, NULL);
    }else if(value > (*node)->value) _insertNode(&(*node)->right, value, *node);
    else if(value < (*node)->value) _insertNode(&(*node)->left, value, *node);
};

struct node * newNode(int value, NODE* father, struct node* left, struct node* right){
    struct node* newnode = malloc(sizeof(struct node));
    newnode->value = value;
    newnode->color = (*father == NULL)? BLACK : RED;
    newnode->left = left;
    newnode->father = *father;
    newnode->right = right;
    return newnode;
}

void inorder(NODE node){

    /*
        A parte recursiva para p
        ercorrer a arvore em ordem 
        da esquerda para direita.
    */

    if(node->left != NULL) inorder(node->left);
    printf(", %d sendo sua cor %s sendo o pai %d\n" ,node->value, (node->color) ? "RED" : "BLACK", (node->father) ? node->father->value : 0);
    caminho(&node);
    if(node->right != NULL) inorder(node->right);
    return;
}



void preorder(NODE node){

    /*
        A parte recursiva da função 
        que devolve a raiz e vai ate 
        nao ter mais elementos a serem
        imperessos.
    */

    printf(", %d",node->value);
    if(node->left != NULL) preorder(node->left);
    if(node->right != NULL) preorder(node->right);
    return;
}

bool BinarySearch(NODE node,int arg){

    /*
        Essa função faz a busca binaria e devolve
        um inteiro, sendo a parte recursiva da função,
        podendo adaptar para qualquer coisa.
    */

    if(node->value == arg) return true;
    if(arg < node->value && node->left != NULL) return BinarySearch(node->left,arg);
    else if(arg > node->value && node->right != NULL) return BinarySearch(node->right,arg);
    return false;
}

void freenode(NODE node){

    /*
        Libera a memoria alocada para os nós da arvore.
    */
   /*
    Queue fila;
    newQueue(&fila);
    Enqueue(&fila, node);
    while (fila.size)
    {
        node = Dequeue(&fila);
        if(node->left != NULL) Enqueue(&fila, node->left);
        if(node->right != NULL) Enqueue(&fila, node->right);       
        free(node);
    }
        */
    if(node == NULL) return;

    freenode(node->left);
    freenode(node->right);   
    free(node);

}

bool max(NODE tree){

    /*
        Procura pelo maior elemento na arvore.
    */

    if(tree == NULL) return false;
    NODE aux = tree;
    while(aux->right != NULL) aux = aux->right;
    if(aux == NULL) return false;
    printf("%d\n", aux->value);    
    return true;    
}

bool min(NODE tree){

    /*
        Procura pelo menor elemento na arvore.
    */

    if(tree == NULL) return false;
    NODE aux = tree;
    while(aux->left != NULL) aux = aux->left;
    if(aux == NULL) return false;
    printf("%d\n", aux->value);    
    return true;    
}

void porlevel(NODE tree){

    /*
        Busca por nivel ela
        vai mostrar os elementos da arvore 
        por nivel, sendo dependente de outra 
        estrutura de dados chamado Fila.
    */

    if(tree == NULL) return;
    Queue fila;
    struct node *aux = tree;
    newQueue(&fila);
    Enqueue(&fila, aux);
    printf("Porlevel>>>\n");
    while (fila.size)
    {
        aux = Dequeue(&fila);
        if(aux->left) Enqueue(&fila, aux->left);
        if(aux->right) Enqueue(&fila, aux->right);       
        printf("%d, ",aux->value);
    }
    
    printf("\n");
}

int heigth(NODE tree, int len){
    if(tree == NULL) return len;
    len++;
    int left = heigth(tree->left, len);
    int right = heigth(tree->right, len);
    return (left >= right)? left : right;
}

void caminho(NODE *node){
    struct node* aux = (*node);
    while (aux)
    {
        printf("%d, ",aux->value);
        aux = aux->father;
    }
    printf("\n");
}