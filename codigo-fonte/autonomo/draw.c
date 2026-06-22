#include <stdio.h>
#include <stdlib.h>


#pragma pack(push, 1)
struct painel{

    int linha;
    int coluna;
    char **matriz;    

};
#pragma pack(pop)

void freeall(struct painel *dados);

int main(int argc, char *argv[])
{
    int linha = 0, coluna = 0;
    struct painel dados = {0, 0 , NULL};
    if(argc == 2) printf("%i, %li\n", argc, sizeof(dados));
    else if(argc > 2) return 1;
    else
    {   
        printf("digite o tamanho da linha e da coluna\n");
        scanf(" %d %d",&linha, &coluna);
        printf("%d, %d\n", linha, coluna);
            if(coluna <= 0 || linha <= 0) return 1;
        dados.linha = linha;
        dados.coluna = coluna;
        dados.matriz = (char **)malloc(linha * sizeof(char *));
        for(int i = 0; i < linha; i++)dados.matriz[i] = (char *)malloc(coluna * sizeof(char));
        for(int i = 0; i < linha ; i++)
        {
            for(int j  = 0; j < coluna; j++)
            {
                dados.matriz[i][j] = '@';
                printf("%c", dados.matriz[i][j]);
            }
            printf("\n");
        }
        freeall(&dados);
    }
    
    return 0;
}
void freeall(struct painel *dados)
{
    
    for(int i = 0; i < dados->linha ; i++)
    {
            free(dados->matriz[i]);
    }
    free(dados->matriz);
}
