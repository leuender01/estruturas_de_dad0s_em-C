#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char tab_bombas[6][6] = {
    {'O','O','O','O','O','O'},
    {'O','O','O','O','O','O'},
    {'O','O','O','O','O','O'},
    {'O','O','O','O','O','O'},
    {'O','O','O','O','O','O'},
    {'O','O','O','O','O','O'}
},tabuleiro[6][6] = {
    {'O','O','O','O','O','O'},
    {'O','O','O','O','O','O'},
    {'O','O','O','O','O','O'},
    {'O','O','O','O','O','O'},
    {'O','O','O','O','O','O'},
    {'O','O','O','O','O','O'}
};

void print_front(void){
    puts("___________CAMPO-MINADO___________\n");
    printf("\t");
    for(int i = 0; i<6; i++)printf(" %d ", i);
    printf("\n\n");
    for(int i = 0; i<6; i++){
        printf("%d\t", i);
        for(int j = 0; j<6; j++){
            printf(" %c ",tabuleiro[j][i]);
        };
        printf("\n");
    };
};

void print_bek(void){
    puts("___________CAMPO-BOMBAS___________\n");
    printf("\t");
    for(int i = 0; i<6; i++)printf(" %d ", i);
    printf("\n\n");
    for(int i = 0; i<6; i++){
        printf("%d\t", i);
        for(int j = 0; j<6; j++){
            printf(" %c ",tab_bombas[j][i]);
        };
        printf("\n");
    };
};

void limpar_buffer(void){
    while (getchar() != '\n' && getchar() != EOF);
};

void sorted(void){
    srand(time(NULL));
    for(int linha =0; linha<6; linha++){
       int bombas_linha = 0;
        while(bombas_linha < 2){
            int colum = rand() % 6;
            if(tab_bombas[linha][colum]=='O'){
                tab_bombas[linha][colum] = 'X';
                bombas_linha++;
            };
        };
    };
};

char win(char * victory){
    if(*victory=='@') return '@';
    short int vazios = 0, bombas = 0;
    for(int i = 0; i<6; i++){
        for(int j = 0; j<6; j++){
            if(tab_bombas[i][j] == 'O' && tabuleiro[i][j] == 'H') vazios++;
            if(tab_bombas[i][j] == 'X') bombas++;
        };    
    };
    printf(" bombas: %hd, vzaios: %hd\n", bombas, vazios);
    if((bombas + vazios) == 36) return 'W';
    return 'C';
};
char select_bomm(void){
    short int linha, collum;
    char modo;
    printf("voce que marcar (*) ou arriscar (H)?\n");
    modo = getchar();
    printf("Digite a linha e coluna ");
    scanf(" %hd %hd", &linha, &collum);
    if(tab_bombas[collum][linha] == 'X' && modo == 'H'){
        tabuleiro[collum][linha] = '@';
        limpar_buffer();
        return '@';
    }else if(tab_bombas[collum][linha] != 'H' && modo == 'H'){
        tabuleiro[collum][linha] = 'H';
        limpar_buffer();
        return 'C';
    }   
    if(modo == '*'){
        tabuleiro[collum][linha] =  modo;
        limpar_buffer();
        return 'C';
};


};


int main(){
    char victory = 'C';
    sorted();
    while(victory == 'C'){
    //system("clear");
    print_bek();
    print_front();
    victory = select_bomm();
    victory = win(&victory);
    };

    switch (victory)
    {
    case '@':
        printf("BOMM\n");
        break;
    case 'W':
        printf("PARABENS\n");
        break;
    }
    return 0;
};