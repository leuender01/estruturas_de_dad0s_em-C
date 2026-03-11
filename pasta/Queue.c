#include <stdio.h>
#include <stdlib.h>
#include "StructureDate.h"

void newQueue(Queue *p){
	p->tail = NULL;
	p->front = NULL;
	p->size = 0;
};
int empytQueue(Queue *p){
	return p->size == 0;
};
int isFullQueue(Queue *p){
	return p->size == TAM_MAX;
};
void Enqueue(Queue *p, int value){
	if(!isFullQueue){
		printf("Queue is Full\n");
		return;
	};
	Element *novo = (Element*)malloc(sizeof(Element));
	if(novo){
		novo->date = value;
		novo->prox = NULL;
		if(p->front == NULL){ 
			p->front = novo;
		 }else{
			p->tail->prox = novo;
		};
		p->tail = novo;
		p->size++;
		}else{
			printf("memory Error\n");
		};
};
int Dequeue(Queue *p){
	if(empytQueue(p)){
		printf("Queue is empyt\n");
		return -1;
	};
	Element *temp = p->front;
	int value = temp->date;
	p->front = p->front->prox;
	if(p->front == NULL){
		p->tail =NULL;
	};
	free(temp);
	p->size--;
	return value;

};
int peekQueue(Queue *p){
	if(p->front == NULL) return -1;
	return p->front->date;
};
