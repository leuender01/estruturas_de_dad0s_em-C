#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_X 20
#define MAX_Y 20
#define MOVE_UP(x, len) ((x - 1 + len) % len)
#define MOVE_DOWN(x, len) ((x + 1) % len)
#define TAM_ARRAY(arr) (sizeof(arr)/sizeof(arr[0]))


struct player
{
    bool game;
    int8_t x, y;
    long int playerX, playerY;
    
};

const char *campos[] = 
{
    "[   ]",
    "[ X ]",
    "[ O ]"
};

int stepy = 0,stepx =  0;
int table[3][3] = {0};

void reset_array(int tabe[3][3]);
void inicializar(struct player *player);
bool mover(struct player *player, bool *vencedor);
bool vitoria(struct player *player, bool *vencedor);
bool empate(void);

void telavitoria(bool *vencedor, struct player *player);
void menu(void);
void printtable(struct player *player);
void help(void);
void sair(void);
void limpar(void);

int main(void)
{  
    struct player player;
    inicializar(&player);
    bool vencedor;
    
    while(true)
    {
        
        if(mover(&player, &vencedor))
        { 
            if(vencedor) player.playerY += 1;
            else player.playerX += 1;
            reset_array(table);
        }else if(empate())
        {
            reset_array(table);
        }
        if(player.playerX > 5 || player.playerY > 5)  telavitoria(&vencedor,&player);
        printtable(&player);
    }
    sair();

    return 0;
}

void sair(void)
{
    endwin();
    exit(0);
}

void printtable(struct player *player)
{
    stepy = 0;
    attron(COLOR_PAIR(2));
    mvprintw(MAX_X - 2, MAX_Y - 2,"=====JOGO_DA_VELHA=====");
    mvprintw(MAX_X + 7, (MAX_Y * 2) + 12,"%s",campos[player->game + 1]);
    mvprintw(MAX_X, (MAX_Y * 2) + 6,"playerX VS playerY");
    mvprintw(MAX_X + 3, (MAX_Y * 2) + 6,"   %li    X     %li",player->playerX, player->playerY);
    attroff(COLOR_PAIR(2));
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {

            if(player->x == i && player->y == j) attron(A_REVERSE);     
            mvprintw(MAX_X + stepy + i, MAX_Y + stepx + j,"%s",campos[(table[i][j] >= 0 && table[i][j] < 3) ? table[i][j] : 0]);
        
            attroff(A_REVERSE);
            stepx += 6;
          }

        stepy += 3; 
        stepx = 0;
           
        }
    }



void inicializar(struct player *player)
{  
    player->x = 0;
    player->y = 0; 
    player->playerX = 0;
    player->playerY = 0;

    initscr();
    start_color();
    
    init_pair(1, COLOR_WHITE, COLOR_BLACK); 
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    init_pair(4, COLOR_BLACK, COLOR_BLACK);
  
    bkgd(COLOR_PAIR(1));

    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(300);
}
bool mover(struct player  *player, bool *vencedor)
{
        int c = getch();
        switch (c)
        {
        case KEY_LEFT:
            player->y = MOVE_UP(player->y, 3);
            break;
        case KEY_RIGHT:
            player->y = MOVE_DOWN(player->y, 3);
            break;
        case KEY_UP:
            player->x = MOVE_UP(player->x, 3);
            break;

        case KEY_DOWN:
            player->x = MOVE_DOWN(player->x, 3);
            break;

        case 10:

            if(table[player->x][player->y] <= 0)
            {
            table[player->x][player->y] = player->game + 1;
            player->game = !player->game;
            }

            break;
        default:

            if(c == 'q' || c == 'Q' || c == 27) menu();
            break;

        }
       return  vitoria(player, vencedor);
}

bool vitoria(struct player *player, bool *vencedor)
{
    int8_t vcoluna = 0, vlinha = 0, vtransversal = 0, ivtransversal = 0;
    bool atual = player->game;

    for(int game = 0; game < 2; game++)
    {
        for(int linha = 0; linha < 3; linha++)
        {
            for(int coluna = 0; coluna < 2; coluna++)
            {
                if(table[linha][coluna] == atual + 1 && table[linha][coluna + 1] == atual + 1) vlinha++;
                if(table[coluna][linha] == atual + 1  && table[coluna + 1][linha] == atual + 1) vcoluna++;
                if(table[coluna][coluna] == atual + 1 && table[coluna + 1][coluna + 1] == atual + 1) vtransversal++;
                if(table[coluna][(2 - coluna)] == atual + 1 && table[coluna + 1][((2 - coluna) - 1)] == atual + 1) ivtransversal++;
                
            }
            *vencedor = atual;
            if(vlinha >= 2 || vcoluna >= 2 || vtransversal >= 2 || ivtransversal >= 2) return true;
            vlinha = 0;
            vcoluna = 0;
            vtransversal = 0;
            ivtransversal = 0;
        }
        
       
        atual = !atual;
    }  
    return false;
}


void menu(void)
{
    char *select[3] =
    {
        "INICIAR",
        " HELP",
        " EXIT"
    };

    int8_t len = TAM_ARRAY(select), destaque = 0;
    bool prox = true;

    limpar(); 

    while (prox)
    {
    attron(COLOR_PAIR(1));
    for (int a = 0; a < 21; a++)
    {
        for (int b = 0; b < 60; b++)
        {
            if (a == 0 || a == 20 || b == 0 || b == 59)
                mvprintw(a, b, "*");
        }
    }

    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(2));
        for (int a = 0; a < 3; a++)
        {
            if (a == destaque)
            {
                attron(A_REVERSE);
                mvprintw(10 + a, 25, "->%s<-", select[a]);
                attroff(A_REVERSE);
            }
            else
            {
                mvprintw(10 + a, 25, "  %s  ", select[a]);
            }
        };

        int16_t c = getch();

        switch (c)
        {
        case KEY_UP:
            destaque = MOVE_UP(destaque, 3);
            break;    

        case KEY_DOWN:
            destaque =  MOVE_DOWN(destaque, 3);
            break;

        case 10:
            if (destaque == len - 1) sair();
            if (destaque == len - 2) help();
            else if (destaque == len - 3) prox = !prox;
            break;

        default:
            break;
        }
    attroff(COLOR_PAIR(2));

    limpar();
    }
}
void help(void)
{
    char *intrucoes[] = 
    {
        "<Seta para esquerda>: movimenta para esquerda",
        "<Seta para direita>: movimenta para direita",
        "<Seta para baixo>: movimenta para baixo",
        "<Seta para cima>: movimenta para cima",
        "<Tecla ESC>: acesso ao menu", 
        "<Tecla Enter> seleciona"
    };

    init_pair(5, COLOR_BLACK, COLOR_YELLOW); 
    bool prox = false;
   
    limpar();

    attron(COLOR_PAIR(5));
    mvprintw((MAX_X *2) - 2 , 1, "%s", "precione \"q\" para sair" );
    attroff(COLOR_PAIR(5));
    
    attron(COLOR_PAIR(1));

    for (int a = 0; a < MAX_X * 2; a++)
    {
        for (int b = 0; b < 60; b++)
        {
            if (a == 0 || a == (MAX_X * 2) - 1  || b == 0 || b == 59)
                mvprintw(a, b, "*");
        }
    }

    for(int register i = 0; i < 6; i++)  mvprintw(2 + i, 3,"%s",intrucoes[i]);
    attroff(COLOR_PAIR(1));

    while (!prox)
    {
        int16_t c = getch();
        if((c == 'q' || c == 'Q'))  prox = !prox;
    }
    limpar();
}

void limpar(void)
{

    attron(COLOR_PAIR(4));
    for (int a = 0; a <( MAX_X * 5); a++)
    {
        for (int b = 0; b < (MAX_Y * 5); b++)
        {
            mvprintw(a, b, " ");
        }
    }
    attroff(COLOR_PAIR(4));
}

void telavitoria(bool *vencedor, struct player *player)
{    
    const char *instrucoes[2] = 
    {
    "REINICIAR", 
    "SAIR"
    };

    int8_t destaque = 0, len = TAM_ARRAY(instrucoes);
    bool prox = 0;

    limpar();


    while (!prox)
    {
    attron(COLOR_PAIR(1));
    for (int a = 0; a < 21; a++)
    {
        for (int b = 0; b < 60; b++)
        {
            if (a == 0 || a == 20 || b == 0 || b == 59)
                mvprintw(a, b, "*");
        }
    }

    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(2));
    mvprintw(10, 20, "%s, %s", "PARABENS O VENCEDOR FOI", campos[*vencedor + 1]);

    for (int a = 0; a < 2; a++)
        {
            if (a == destaque)
            {
                attron(A_REVERSE);
                mvprintw(MAX_X - 2, 2 + (a * 45), "->%s<-", instrucoes[a]);
                attroff(A_REVERSE);
            }
            else
            {
                mvprintw(MAX_X - 2, 2 + (a * 45), "  %s  ", instrucoes[a]);
            }
        };

        int16_t c = getch();

        switch (c)
        {
        case KEY_RIGHT:
            destaque = MOVE_UP(destaque, 2);
            break;    

        case KEY_LEFT:
            destaque =  MOVE_DOWN(destaque, 2);
            break;

        case 10:
            if (destaque == len - 1) sair();
            if (destaque == len - 2)
            {
                player->playerX = 0;
                player->playerY = 0;
                prox = !prox;
            }
            break;

        default:
            break;
        }
    attroff(COLOR_PAIR(2));

    limpar();
    }

}
void reset_array(int tabe[3][3])
{
    for(int8_t i = 0; i < 3; i++)
    {
        for(int8_t a = 0; a < 3; a++) 
        {
            tabe[i][a] = 0;
        }
    }
}
bool empate(void)
{
    int8_t velha = 0;
    for(int8_t i = 0; i < 3; i++)
    {
        for(int8_t a = 0; a < 3; a++) 
        {
           if(table[i][a] > 0) velha++; 
        }
    }
    if(velha >= 9) return true;
    return false;
}
