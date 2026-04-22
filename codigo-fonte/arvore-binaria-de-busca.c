#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "arvore-binaria-de-busca.h"

/*
    A Parte do codigo em si nao tem utilidade real apenas eu 
    aprendendo a fazer uma.
*/

TREE init(TREE tree){

    /*
        inicializa zerando todos os elementos dentro ta arvore.
    */

    tree = malloc(sizeof(BinarySearchtree));
    if(tree == NULL) return tree;
    tree->size = 0;
    tree->node = NULL;
    return tree;
}

struct no* insertNode(struct no *node, int value,int* count){
    
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
        *count = *count + 1;
        return node;
    };

    if(value < node->value){
        node->left = insertNode(node->left, value, count);
    }else if(value > node->value){
        node->right = insertNode(node->right, value, count);
    }; 
    return node;
}

bool insert(TREE tree,int value){

    /*
        Essa parte chama a função 
        recursiva que insere tambem 
        compara se a inserção foi bem
        sucedida retornando true ou false.
    */

    int new_cont = 0;
    tree->node = insertNode(tree->node,value,&new_cont);
    if(new_cont != 0){
        tree->size = tree->size + new_cont;
        return true;
    }
    return false;
}

void inorderDFS(struct no *node){

    /*
        A parte recursiva para p
        ercorrer a arvore em ordem 
        da esquerda para direita.
    */

    if(node->left != NULL) inorderDFS(node->left);
    printf(", %d",node->value);
    if(node->right != NULL) inorderDFS(node->right);
    return;
}

void inorder(TREE tree){

    /*
        A parte que inicia a recursão 
        e da uma organizada na saida.
    */

    struct no *node = tree->node;
    printf("inorder>>");
    inorderDFS(node);
    printf("\n");
}

void preorderDFS(struct no *node){

    /*
        A parte recursiva da função 
        que devolve a raiz e vai ate 
        nao ter mais elementos a serem
        imperessos.
    */

    printf(", %d",node->value);
    if(node->left != NULL) preorderDFS(node->left);
    if(node->right != NULL) preorderDFS(node->right);
    return;
}

void preorder(TREE tree){

    /*
        A parte que chama a função recursiva.
    */

    struct no *node = tree->node;
    printf("preorder>>");
    preorderDFS(node);
    printf("\n");
}

int BinarySearchBFS(struct no *node,int arg,int result){

    /*
        Essa função faz a busca binaria e devolve
        um inteiro, sendo a parte recursiva da função,
        podendo adaptar para qualquer coisa.
    */

    if(node->value == arg) return node->value;
    if(arg < node->value && node->left != NULL){
        result = BinarySearchBFS(node->left,arg,result);
    }else if(arg > node->value && node->right != NULL){
        result = BinarySearchBFS(node->right,arg,result);
    };
    return result;
}

int BinarySearch(TREE tree, int arg){

    /*
        Essa função chama a a recurção 
        da Busca Binaria e compara se achou alguma coisa.
    */


    int result = 0;
    result = BinarySearchBFS(tree->node, arg,result);
    if(result != arg) printf("nao esta\n");
    return result;
}

void freenode(struct no *node){

    /*
        Libera a memoria alocada para os nós da arvore.
    */

    if(node == NULL) return;
    freenode(node->left);
    freenode(node->right);
    free(node);
    return;
}

bool freeTree(TREE tree){

    /*
        Libera a memoria que a arvore aloca.
    */

    freenode(tree->node);
    free(tree);
    return true;
}

bool max(TREE tree){

    /*
        Procura pelo maior elemento na arvore.
    */

    if(tree == NULL) return false;
    struct no *aux = tree->node;
    while(aux->right != NULL) aux = aux->right;
    if(aux == NULL) return false;
    printf("%d\n", aux->value);    
    return true;    
}

bool min(TREE tree){

    /*
        Procura pelo menor elemento na arvore.
    */

    if(tree == NULL) return false;
    struct no *aux = tree->node;
    while(aux->left != NULL) aux = aux->left;
    if(aux == NULL) return false;
    printf("%d\n", aux->value);    
    return true;    
}

int _min(struct no *aux){

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

struct no* removeNodeDfs(struct no *node, int arg, TREE len){

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
        node->left = removeNodeDfs(node->left,arg,len);
    }else if(arg > node->value && node->right != NULL){
        node->right = removeNodeDfs(node->right,arg,len);
    }else if(node->value == arg){
        if(node->left == NULL){
            struct no *temp = node->right;
            free(node);
            len->size--;
            return temp;
        }else if(node->right == NULL){
            struct no *temp = node->left;
            free(node);
            len->size--;
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

    /*
        Inicia a recurção e ao final ela 
        retorna true caso um  nó tenha sido removido.
    */

    int old_size = tree->size;
    tree->node = removeNodeDfs(tree->node, arg,tree);
    return !(tree->size == old_size);
}

void porlevel(TREE tree){

    /*
        Busca por nivel ela
        vai mostrar os elementos da arvore 
        por nivel, sendo dependente de outra 
        estrutura de dados chamado Fila.
    */

    if(tree == NULL) return;
    Queue fila;
    struct no* aux = tree->node;
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

int heightDFS(struct no* node, int len){

    /*
        Função para calcular a altura de uma arvore,
        pretendo usar futuramente para colar arvores AvL.
    */

    if(node == NULL) return len;
    len++;
    int left = heightDFS(node->left, len);
    int right = heightDFS(node->right, len);
    if(left >= right) return left;
    return right;
}

int height(TREE tree){
    int size = heightDFS(tree->node, 0);
    return size;
}