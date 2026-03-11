#include <stdio.h>
#include "StructureDate.h"

int main(void){
	//Stack Pilha;
	//newStack(&Pilha);
	
	//pushStack(&Pilha,3);
	//pushStack(&Pilha,4);
	//pushStack(&Pilha,6);
	//pushStack(&Pilha,8);		
	//pushStack(&Pilha,71);
	//popStack(&Pilha);

	//printf("%d\n",peekStack(&Pilha));

	Queue *Fila;
	newQueue(Fila);
	Enqueue(Fila, 2);
	Enqueue(Fila,3);
	printf("%d, %d\n",Dequeue(Fila),peekQueue(Fila));

	return 0;
};
