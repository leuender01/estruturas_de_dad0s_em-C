#include <stdio.h>

int main(){
    float num1, num2;
    float rsult;
    char op;
  
    printf("digite o primeiro numero: ");
    scanf("%f", &num1);
  
    printf("\ndigite a operação: ");
    scanf("%c", &op);
  
    printf("digite o segundo numero: ");
    scanf("%f", &num2);

    switch (op){
    case '*':
        rsult = num1 * num2;
        break;
    
    default:
        break;
    };
};