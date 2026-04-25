#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

/*
    isso e so um arquivo de cabeçalho contendo 
    prototipos de funções, usadas em um arquivo 
    separado, tava encontrando muitos problemas 
    em inserir coisas que eu ja fiz antes entao 
    decidi separar cada parte importante do codigo
    em um arquivo, que eu possa mecher um por vez.
*/

//--------------Bibliotecas_De_Codigos------------------

#include <stdbool.h> // biblioteca de booleanos
#include "arvore-base.h" // inclui a estrutura base para uma arvore
#include "Queue.h" // inclui o cabeçalho do codigo da fila

//---------------Prototipos_de_funções------------------

// <<<<<<<<<< INICIALIZA >>>>>>>>>>>>

TREE init(TREE tree); // prototipo de função que inicializa a arvore

// <<<<<<<<<< INSERÇÃO >>>>>>>>>>>>

bool insert(TREE tree,int value); // função que inicia o processo de inserção
struct no* insertNode(struct no *node, int value,int* count);// prototipo de função principal que insere um no

// <<<<<<<<<<<<<<<<< BUSCA >>>>>>>>>>>>>>>>>>>

void inorderDFS(struct no *node);// percorre a arvore na ordem 
void inorder(TREE tree);// função recursiva
void preorderDFS(struct no *node);// percorre da raiz ate nao ter mais elementos sempre começando da esquerda para direita
void preorder(TREE tree);// função recursiva
void porlevel(TREE tree);// função que busca por nivel e necessario uma estrutura de dados semelhante a uma fila
bool BinarySearch(TREE tree, int arg);// faz a busca binaria dentro da arvore
bool BinarySearchBFS(struct no *node,int arg);// a parte recursiva sa busca binaria
bool max(TREE tree); // mostra o maior elemento dentro de uma arvore binaria
bool min(TREE tree); // mostra o menor elemento dentro de uma arvore binaria
int height(TREE tree);// Função que chama a função recursiva
int heightDFS(struct no* node, int len);// FUnção principal que vai procurar o mair caminho dentro da arvore

// <<<<<<<<<< REMOVE UM NÓ DA ARVORE >>>>>>>>>>>>

bool removeNode(TREE tree, int arg);// função que inicia o preocesso de remover um no sem quebrar a arvore
struct no* removeNodeDfs(struct no *node, int arg, TREE len);// a parte recursiva da remoção
int _min(struct no *aux); // usada em conjunto com a função de remover pode ser substituida

//<<<<<<<<< LIBERA A MEMORIA ALOCADA >>>>>>>>>>>>>>

bool freeTree(TREE tree);// libera a memoria alocada da arvore
void freenode(struct no *node); // libera a memoria alocado nos nós

#endif