#include <stdio.h>
#include "data.h"

const char *SEMANA[] = {
    "Domingo",
    "Segunda-feira",
    "Terça-feira",
    "Quarta-feira",
    "Quinta-feira",
    "Sexta-feira",
    "Sabado",
};

const char *MESES[] = {
    "Janeiro",
    "Fevereiro",
    "Março",
    "Abril",
    "Maio",
    "Junho",
    "Julho",
    "Agosto",
    "Setembro",
    "Outubro",
    "Novembro",
    "Dezembro",
};

void exibir(void){
    for(register int i = 0; i < 7; i++) printf("%s\n", SEMANA[i]);
}