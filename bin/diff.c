#include <stdio.h>

typedef struct{
    int value;
    node *prox;
}node;

int* add_node(node no, node *prox){
    
};

int main(int arg, char* argv[]){
    if(arg != 3) return 1;
    FILE *f1, *f2;

    f1 = fopen(argv[1], "rb");
    f2 = fopen(argv[2], "rb");
    
    if(f1 == NULL) return 1;
    if(f2 == NULL) return 1; 
    //char buffer1,buffer2;

    fseek(f1,0,SEEK_END);
    long arquiv1 = ftell(f1);
    
    fseek(f2,0,SEEK_END);
    long arquiv2 = ftell(f2);
    
    fclose(f1);
    fclose(f2);
    
    if(arquiv1 > arquiv2) printf("++%s\n--%s\n",argv[1],argv[2]);
    if(arquiv1 < arquiv2) printf("++%s\n--%s\n",argv[2],argv[1]);

    return 0;
};