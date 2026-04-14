#ifndef STRUCTUREDATE_H
#define STRUCTUREDATE_H
//------------Consts--------------
#define TAM_MAX 100


//------------Stack----------------

typedef struct{int items[TAM_MAX]; int top;} Stack;
void newStack(Stack *p);
int empytStack(Stack *p);
int isFullStack(Stack *p);
void pushStack(Stack *p, int date);
int popStack(Stack *p);
int peekStack(Stack *p);

//------------Queue-----------------

typedef struct Element{int date; struct Element *prox;} Element;
typedef struct{ int size; Element *tail; Element *front;} Queue;
void newQueue(Queue *p);
int empytQueue(Queue *p);
int isFullQueue(Queue *p);
void Enqueue(Queue *p, int value);
int Dequeue(Queue *p);
int peekQueue(Queue *p);

#endif
