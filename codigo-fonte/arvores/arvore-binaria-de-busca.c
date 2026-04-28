#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "arvore-binaria-de-busca.h"
#include "arvore-de-busca-AVL.h"// caso queira incluir rotaçoes na inserção da arvore binaria tem que incluir isso

/*
    A Parte do codigo em si nao tem utilidade real apenas eu 
    aprendendo a fazer uma.
*/

NODE init(NODE node){

    /*
        inicializa zerando todos os elementos dentro do node.
    */
    node = malloc(sizeof(struct no));
    if(node == NULL) return NULL;
    node->height = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct no * insertNode(NODE node, int value){
    
    /*
        A o mesmo tempo que cria um novo nó ele realizar uma travercia 
        usando a busca binaria mantendo a arvore com os elementos com
        maior valor a direito e os menores ao lado esquerdo.
    */

    if(node == NULL){
        node = malloc(sizeof(struct no));
        if(node == NULL) return node;
        node->value = value;
        node->left = NULL;
        node->right = NULL;
        return node;
    };

    if(value < node->value){
        node->left = insertNode(node->left, value);
        node->height = height(node, 0);
        return node;
    }else if(value > node->value){
        node->right = insertNode(node->right, value);
        node->height = height(node, 0);
        return node;
    }; 
    height(node, 0);
    node = balancear(node);
    return node;
}


void inorder(NODE node){

    /*
        A parte recursiva para p
        ercorrer a arvore em ordem 
        da esquerda para direita.
    */

    if(node->left != NULL) inorder(node->left);
    printf(", %d",node->value);
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

bool BinarySearchBFS(NODE node,int arg){

    /*
        Essa função faz a busca binaria e devolve
        um inteiro, sendo a parte recursiva da função,
        podendo adaptar para qualquer coisa.
    */

    if(node->value == arg) return true;
    if(arg < node->value && node->left != NULL) return BinarySearchBFS(node->left,arg);
    else if(arg > node->value && node->right != NULL) return BinarySearchBFS(node->right,arg);
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

int _min(NODE aux){

    /*
        Usando em conjunto com a função de remoção, 
        sendo necessaria para balancear a arvore.
        Nao precisa necessariamente criar um função separada, 
        da para juntar com função de cima, mais prefiro fazer separada.
        A o final ela retorna o no com o menor elemento da arvore.
    */

    if(aux == NULL) return -1;
    while(aux->left != NULL) aux = aux->left;   
    return aux->value;    
}

struct no *removeNodeDfs(NODE node, int arg){

    /*
        Função recursiva que vai remover o no em tres casos no primeiro se o 
        no existir e nao tiver filhos ele vai sobrescrever com o valor NULL e 
        depois liberar a meoria, caso tenha apenas um filhos esse filho vira o
        novo no, e caso ele tenha os dois ele vai pegar o menor no a direita da
        raiz e vai virar  novo no da arvore apagando a sua posição anterior, 
        e claro usando a Busca binaria para percorrer a arvore.
    */


    if(node == NULL) return NULL;
    if(arg < node->value && node->left != NULL){
        node->left = removeNodeDfs(node->left,arg);
        return node;
    }else if(arg > node->value && node->right != NULL){
        node->right = removeNodeDfs(node->right,arg);
        return node;
    }else if(node->value == arg){
        if(node->left == NULL){
            NODE temp = node->right;
            free(node);
            return temp;
        }else if(node->right == NULL){
            NODE temp = node->left;
            free(node);
            return temp;
        }else{
            int aux = _min(node->right);
            if(aux == -1) return node;
            node->value = aux;
            node->right = removeNodeDfs(node->right, aux);
            return node;    
        };
    };
    return balancear(node);
}

bool removeNode(NODE tree, int arg){

    /*
        Inicia a recurção e ao final ela 
        retorna true caso um  nó tenha sido removido.
    */
    int old_size = tree->height;
    tree = removeNodeDfs(tree, arg);
    return !(tree->height == old_size);
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
    NODE aux = tree;
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

int height(NODE node, int len){

    /*
        Função para calcular a altura de uma arvore,
        pretendo usar futuramente para colar arvores AvL.
    */

    if(node == NULL) return len;
    len++;
    int left = height(node->left, len);
    int right = height(node->right, len);
    if(left >= right) return left;
    return right;
}