#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <stdbool.h>

#include "tetris.h"
// #include "cor.h"

const MODELO BLOCOS[] = {
    {
        .max_rot = 1,
        .forma =
            {{
                // QUADRADO
                {'#', '#', '#'}, //   # # #
                {'#', '#', '#'}, //   # # #
                {'#', '#', '#'}  //   # # #
            }},
    },
    {.max_rot = 4, .forma = {                   // PEÇA ELLE
                             {{'#', '#', '#'},  // # # #
                              {'#', ' ', ' '},  // #
                              {'#', ' ', ' '}}, // #

                             {{'#', ' ', ' '},  // #
                              {'#', ' ', ' '},  // #
                              {'#', '#', '#'}}, // # # #

                             {{'#', '#', '#'},  // # # #
                              {' ', ' ', '#'},  //     #
                              {' ', ' ', '#'}}, //     #

                             {{' ', ' ', '#'},    //     #
                              {' ', ' ', '#'},    //     #
                              {'#', '#', '#'}}}}, // # # #

    {.max_rot = 4, .forma = {                   // PECA TÊ
                             {{'#', '#', '#'},  // # # #
                              {' ', '#', ' '},  //   #
                              {' ', '#', ' '}}, //   #

                             {{' ', ' ', '#'},  //     #
                              {'#', '#', '#'},  // # # #
                              {' ', ' ', '#'}}, //     #

                             {{' ', '#', ' '},  //   #
                              {' ', '#', ' '},  //   #
                              {'#', '#', '#'}}, // # # #

                             {{'#', ' ', ' '},    // #
                              {'#', '#', '#'},    // # # #
                              {'#', ' ', ' '}}}}, // #
    {.max_rot = 2, .forma = {
                       // PECA I
                       {{'#', ' ', ' '},  // #
                        {'#', ' ', ' '},  // #
                        {'#', ' ', ' '}}, // #

                       {{' ', ' ', ' '},  //
                        {' ', ' ', ' '},  // # # #
                        {'#', '#', '#'}}, //
                   }},
    {.max_rot = 4, .forma = {                   // PECA Z
                             {{' ', '#', ' '},  //   #
                              {' ', '#', '#'},  //   # #
                              {' ', ' ', '#'}}, //     #

                             {{' ', ' ', ' '},  //
                              {' ', '#', '#'},  //   # #
                              {'#', '#', ' '}}, // # #

                             {{' ', ' ', '#'},  //     #
                              {' ', '#', '#'},  //   # #
                              {' ', '#', ' '}}, //   #

                             {{' ', ' ', ' '},    //
                              {'#', '#', ' '},    // # #
                              {' ', '#', '#'}}}}, //   # #
    {.max_rot = 4, .forma = {                     // PECA QUADRADO ELLE
                             {{'#', '#', '#'},    // # # #
                              {'#', '#', '#'},    // # # #
                              {' ', '#', '#'}},   //   # #

                             {{'#', '#', '#'},  // # # #
                              {'#', '#', '#'},  // # # #
                              {'#', '#', ' '}}, // # #

                             {{'#', '#', ' '},  // # #
                              {'#', '#', '#'},  // # # #
                              {'#', '#', '#'}}, // # # #

                             {{' ', '#', '#'},    //   # #
                              {'#', '#', '#'},    // # # #
                              {'#', '#', '#'}}}}, // # # #
    {.max_rot = 2, .forma = {                     // PECA LINHA
                             {{'#', ' ', ' '},    // #
                              {' ', '#', ' '},    //   #
                              {' ', ' ', '#'}},   //     #

                             {{' ', ' ', '#'},   //     #
                              {' ', '#', ' '},   //   #
                              {'#', ' ', ' '}}}} // #
};

int main(void)
{
    srand(time(NULL));
    PLAYER player;

    inicializador(&player);

    int c = 0;
    while (1)
    {
        table();
        refresh();
        //napms(100);
        Player(&player);
    }

    sair();

    return 0;
}

void sair(void)
{
    endwin(); // finaliza a bibliotec
    exit(0);
}

void inicializador(PLAYER *player)
{

    player->x = 2;
    player->y = rand() % (TAM_MAX_Y - 5) + 1;
    escolher(player);

    for (register int x = 0; x < TAM_MAX_X; x++)
    {
        for (register int y = 0; y < TAM_MAX_Y; y++)
        {
            if (x == TAM_MAX_X - 1 || y == 0 || y == TAM_MAX_Y - 1 || x == 0)
                matriz[x][y] = '=';
            else
                matriz[x][y] = ' ';
        };
    };

    initscr();     // inicializa a biblioteca
    start_color(); // inicializa as cores

    init_pair(1, COLOR_BLACK, COLOR_BLACK);  // Texto(Branco) | Fundo(Azul)
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); // Texto(Vermelho) | Fundo(Branco)
    init_pair(3, COLOR_WHITE, COLOR_BLACK);  // Texto(Azul) | Fundo(Branco)
    init_pair(4, COLOR_BLUE, COLOR_BLACK);  // Texto(Azul) | Fundo(Branco)

    bkgd(COLOR_PAIR(1));
    noecho();
    //nodelay(stdscr, TRUE);
    timeout(150);
    keypad(stdscr, TRUE);
    /* bkgd(COLOR_PAIR(1));  Aqui nós definiremos que a cor de fundo do nosso
    programa será azul e a cor dos textos será branca.

                                      attron(COLOR_PAIR(3)); Estamos alterando o par de cores para 3 em vez
                                      de utilizar o par de cor por omissão(1).

                                      move(2,1);  Aqui estamos movendo o cursor para a linha 2 coluna 1.
                                      printw("Olá mundo!!!");  Imprimimos um texto na tela na posição acima.
                                      attroff(COLOR_PAIR(3));  Estamos alterando o par com a cor por omissão,
                                      ou seja, retornando para o par de cor 1.
                                      attron(COLOR_PAIR(2));
                                      move(1,6);
    printw("Qualquer tecla para sair."); Imprimimos um texto na tela na
    posição acima.
    attroff(COLOR_PAIR(2));
    */
    attron(COLOR_PAIR(1));
    table();
    attron(COLOR_PAIR(1));
    // refresh();
    // Fica esperando que o usuário aperte alguma tecla
};

void table(void)
{

    for (register int x = 0; x < TAM_MAX_X; x++)
    {
        for (register int y = 0; y < TAM_MAX_Y; y++)
        {
            attron(COLOR_PAIR(3));
            if (matriz[x][y] == '#' || matriz[x][y] == 'X') attron(COLOR_PAIR(2));else attron(COLOR_PAIR(3));
            mvprintw(x, y, "%c", matriz[x][y]);
            attron(COLOR_PAIR(3));
        };
    };
}
void Player(PLAYER *player)
{
    for (register int x = 0; x < 3; x++)
    {
        for (register int y = 0; y < 3; y++)
        {
            if (player->blocos[x][y] == '#')
                matriz[player->x + x][player->y + y] = ' ';
        }
    }
    tetris_clear(player);
    
    int c = getch();
    if (c == KEY_LEFT && player->x > 2)
    {
        (!colision(player, player->x, player->y - 2)) ? player->y-- : player->y;
    }
    else if (c == KEY_RIGHT && player->x < TAM_MAX_X - 4)
    {
        (!colision(player, player->x, player->y + 3)) ? player->y++ : player->y;
    }else if(c == KEY_DOWN)
    {
        (!colision(player, player->x + 2, player->y))? player->x = player->x + 2 : player->x;
    }
    if(c == 'q'){
        rotate(player);
    }else if(c == 27){
        sair();
    }

    Previw(player);
    if (!colision(player, player->x + 1, player->y))
    {
        player->x++;
        for (register int x = 0; x < 3; x++)
        {
            for (register int y = 0; y < 3; y++)
                if (matriz[player->x + x][player->y + y])
                    if (player->blocos[x][y] == '#')
                        matriz[player->x + x][player->y + y] = '#';
        }
        tetris_previw(player);
    }
    else
    {

        for (register int x = 0; x < 3; x++)
        {
            for (register int y = 0; y < 3; y++)
            {
                if (player->blocos[x][y] == '#')
                    matriz[player->x + x][player->y + y] = 'X';
            }
        }

        player->x = 2;
        player->y = TAM_MAX_Y / 2;
        escolher(player);

        if(colision(player, player->x, player->y)) sair();        
    };
}

void rotate(PLAYER *player)
{
    if (player->rotate ==  BLOCOS[player->type].max_rot) player->rotate = 1;
    else player->rotate++;


    

    for(register int x = 0; x < 3; x++){
        for(register int y = 0; y < 3; y++){
            player->blocos[x][y] = BLOCOS[player->type].forma[player->rotate - 1][x][y];
        }
    }
}

void escolher(PLAYER *player)
{
    int tipo = rand() % 7;
    int rot = rand() % BLOCOS[tipo].max_rot;

    player->type = tipo;
    player->rotate = rot;

    for (register int x = 0; x < 3; x++)
    {
        for (register int y = 0; y < 3; y++)
        {
            player->blocos[x][y] = BLOCOS[tipo].forma[rot][x][y];
        }
    }
}

bool colision(PLAYER *player, int index, int indey)
{

    
    for (register int x = 0; x < 3; x++)
    {
        for (register int y = 0; y < 3; y++)
        {
            if (player->blocos[x][y] == '#')
            {
                int targetX = index + x;
                int targetY = indey + y;

                if (targetX >= TAM_MAX_X - 1 || targetY >= TAM_MAX_Y - 1 || targetY <= 0)
                    return true;

                if (matriz[targetX][targetY] == '=' || matriz[targetX][targetY] == 'X')
                    return true;

            }
        }
    }

    return false;
}

void Previw(PLAYER * player)
{
    char previw[7][7];

    for (register int x = 0; x < 7; x++)
    {
        for (register int y = 0; y <= 7; y++)
        {
            if(x < 1 || x > 5 || y < 1 || y > 5) previw[x][y] = '='; 
            else previw[x][y] = ' ';
        }
    }
    for (register int x = 0; x < 3; x++)
    {
        for (register int y = 0; y < 3; y++)
        { 
            previw[2 + x][2 + y] = player->blocos[x][y];
        }
    }

    for (register int x = 0; x < 7; x++)
    {
        for (register int y = 0; y < 7; y++)
        {
            attron(COLOR_PAIR(4));
            if(previw[x][y] == '#') attron(COLOR_PAIR(2));
            mvprintw( x, (TAM_MAX_Y + 5) + y, "%c",previw[x][y]);
            attron(COLOR_PAIR(4));
            
        }
    }
    
    
}

void tetris_previw(PLAYER *player)
{
    int ghost_x = player->x;

    while (!colision(player, ghost_x + 1, player->y)) {
        ghost_x++;
    }
    
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            if (player->blocos[x][y] == '#') {
                // Desenha apenas se a posição estiver vazia na matriz real
                // para não sobrepor a peça que está caindo
                if (ghost_x + x > player->x + 2) { 
                     matriz[ghost_x + x][player->y + y] = '@';
                }
            }
        }
    }

}

void tetris_clear(PLAYER *player)
{
    int ghost_x = player->x;

    while (!colision(player, ghost_x + 1, player->y)) {
        ghost_x++;
    }
    
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            if (player->blocos[x][y] == '#') {
                // Desenha apenas se a posição estiver vazia na matriz real
                // para não sobrepor a peça que está caindo
                if (ghost_x + x > player->x + 2) { 
                     matriz[ghost_x + x][player->y + y] = ' ';
                }
            }
        }
    }

}