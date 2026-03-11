#include <stdlib.h>
#include <stdio.h>

char freeze(void){
    printf("pressione Enter para continuar ou 'q' para sair ...");
    while(getchar() != '\n' );
    if(getchar() == 'q'){
        return '1';
    }else{
        return '0';
    };
};

int main(){
    float num1, num2;
    char op, cond = '0';
    char resul[] = "o resultado e igual a: ";
 
    while (cond == '0'){
    printf("Digite a operação EX:(5*2, 5/2, 5-3, 5+2)\n");

    if(scanf(" %f %c %f", &num1, &op, &num2) == 3){
        switch (op)
        {
        case '*':
            printf("%s %.1f \n", resul, num1 * num2);
            break;
         case '/':
            printf("%s %.1f \n", resul, num1 / num2);
            break;
        case '-':
            printf("%s %.1f \n", resul, num1 - num2);
            break;
         case '+':
            printf("%s %.1f \n", resul, num1 + num2);
            break;
        default:
            printf("Operação invalida\n");
            break;
        }
    }else{
        printf("formato invalido tente novamente\n");
    };
    cond = freeze();
    system("clear");
};
    return 0;
}
