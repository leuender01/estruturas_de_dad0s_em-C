#include <stdio.h>

void func()
{
    char a;
    char *b;
    b = &a;

    for (register int i; i < 100; i++)
    {
        printf("%c", b[i]);
    }
}

int main(void)
{
    char SENHA[] = "SENHA";
    char SENHA2[] = "SENHA2";
    char SENHA3[] = "SENHA3";
    char SENHA4[] = "SENHA4";
    func();
    
    return 0;
}