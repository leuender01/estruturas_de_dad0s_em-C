#include <stdio.h>
#include "data.h"

int main(void)
{
    enum MES hoje = ABRIL;
    printf("mes %s dia %d %s\n", MESES[ABRIL], 2, SEMANA[SABADO] );
    return 0;
}