#include <stdio.h>
#include <stdlib.h>

char tabuleiro[3][3] = {
    {'-','-','-'},
    {'-','-','-'},
    {'-','-','-'}
};

void mostrar_tabuleiro(void){
    for (int j = 0; j < 3; j++){
        for(int i = 0; i<3; i++){
        printf("%c ",tabuleiro[j][i]);
    };
    printf("\n");
    };
};

void select(char* player, char* troca){
    short int linha, coluna;
    printf("Selecione a linha (ex: 0, 1, 2), coluna (ex: 0, 1, 2)");
    scanf(" %hd %hd", &linha, &coluna);
    if(tabuleiro[linha][coluna] == '-'){
        tabuleiro[linha][coluna] = *player;
        *troca = '0';
    }else{
        *troca = '1';
    }; 
};

char win(char* player, char* troca){
    short int victory_line = 0, victory_collum = 0, victory_travarsal = 0, victory_invert = 0;
    if(*troca == '1') printf("digite novemante\n");
    for(int i = 0; i<3; i++){
        if(tabuleiro[i][2-i] == *player) victory_invert++;
        if(tabuleiro[i][i] == *player) victory_travarsal++;
        if(victory_travarsal == 3 || victory_invert == 3) return '1';
        for(int j = 0; j<3; j++){
            if(tabuleiro[i][j] == *player)victory_line++;
            if(tabuleiro[j][i] == *player)victory_collum++;
            if(victory_collum == 3 || victory_line == 3) return '1';
        };
        victory_line = 0;
        victory_collum = 0;
    };
    printf("invert: %d, culum: %d, line: %d, travarsel: %d\n",victory_invert, victory_collum, victory_line, victory_travarsal);
    *player = (*player == 'O' && *troca == '0') ? 'X': 'O';
    return '0';
};

int main(){
    char player = 'O', vct='0', troca= '0';
    
    while (vct == '0')
    {
        mostrar_tabuleiro();
        select(&player, &troca);
        vct = win(&player, &troca);
    };
    
}