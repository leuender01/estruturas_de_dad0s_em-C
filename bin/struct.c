#include <stdio.h>
#include <stdlib.h>

struct variavel
{
    short int a;
    char letra;
};


int main(void){
    struct variavel c,b;
    c.a = 10;
    c.letra='A';
    
    FILE *file = fopen("struct.bin","ab");
    if( file == NULL) return 1;
    fwrite(&c,sizeof(c),1,file);
    fclose(file);

    file = fopen("struct.bin","rb");
    if(file == NULL) return 1;
    fread(&b,sizeof(b),1,file);
    printf("%hd, %c, %ld\n", b.a, b.letra, sizeof(b));

    return 0;
};