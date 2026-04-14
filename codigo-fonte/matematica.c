#include "matematica.h"

int soma(int var, int var2){
    return var + var2;
};
long long int fatorial(int num){
    if(num == 0) return 1;
    return num*fatorial(num-1);
};
long long int fibonaci(int num){
    if(num <= 1) return num;
    return fibonaci(num-1)+ fibonaci(num-2);
};
