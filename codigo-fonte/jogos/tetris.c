#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <inttypes.h>
//#include <unistd.h>

#include "tetris.h"
// #include "cor.h"

long point = 0;
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

    menu();

    inicializador(&player);

    while (1)
    {
        table();
        refresh();

        Player(&player);
        points();
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
    init_pair(4, COLOR_BLUE, COLOR_BLACK);   // Texto(Azul) | Fundo(Branco)

    bkgd(COLOR_PAIR(1));
    noecho();

    keypad(stdscr, TRUE);
}

void table(void)
{

    for (register int x = 0; x < TAM_MAX_X; x++)
    {
        for (register int y = 0; y < TAM_MAX_Y; y++)
        {
            attron(COLOR_PAIR(3));
            if (matriz[x][y] == '#' || matriz[x][y] == 'X')
                attron(COLOR_PAIR(2));
            else
                attron(COLOR_PAIR(3));
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

    int16_t c = getch();
    if (c == KEY_LEFT && player->x > 2)
    {
        (!colision(player, player->x, player->y - 2)) ? player->y-- : player->y;
    }
    else if (c == KEY_RIGHT && player->x < TAM_MAX_X - 4)
    {
        (!colision(player, player->x, player->y + 3)) ? player->y++ : player->y;
    }
    else if (c == KEY_DOWN)
    {
        (!colision(player, player->x + 2, player->y)) ? player->x = player->x + 2 : player->x;
    }
    if (c == 'q')
    {
        rotate(player);
    }
    else if (c == 27)
    {
        menu();
    }
    timeout(300);

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

        if (colision(player, player->x, player->y))
            sair();
    };
}

void rotate(PLAYER *player)
{
    if (player->rotate == BLOCOS[player->type].max_rot)
        player->rotate = 1;
    else
        player->rotate++;

    for (register int x = 0; x < 3; x++)
    {
        for (register int y = 0; y < 3; y++)
        {
            player->blocos[x][y] = BLOCOS[player->type].forma[player->rotate - 1][x][y];
        }
    }
}

void escolher(PLAYER *player)
{
    int8_t tipo = rand() % 7;
    int8_t rot = rand() % BLOCOS[tipo].max_rot;

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

void Previw(PLAYER *player)
{
    char previw[7][7];

    for (register int x = 0; x < 7; x++)
    {
        for (register int y = 0; y <= 7; y++)
        {
            if (x < 1 || x > 5 || y < 1 || y > 5)
                previw[x][y] = '=';
            else
                previw[x][y] = ' ';
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
            if (previw[x][y] == '#')
                attron(COLOR_PAIR(2));
            mvprintw(x, (TAM_MAX_Y + 5) + y, "%c", previw[x][y]);
            attron(COLOR_PAIR(4));
        }
    }
}

void tetris_previw(PLAYER *player)
{
    int8_t ghost_x = player->x;

    while (!colision(player, ghost_x + 1, player->y))
    {
        ghost_x++;
    }

    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            if (player->blocos[x][y] == '#')
            {
                // Desenha apenas se a posição estiver vazia na matriz real
                // para não sobrepor a peça que está caindo
                if (ghost_x + x > player->x + 2)
                {
                    matriz[ghost_x + x][player->y + y] = '@';
                }
            }
        }
    }
}

void tetris_clear(PLAYER *player)
{
    int8_t ghost_x = player->x;

    while (!colision(player, ghost_x + 1, player->y))
    {
        ghost_x++;
    }

    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            if (player->blocos[x][y] == '#')
            {
                // Desenha apenas se a posição estiver vazia na matriz real
                // para não sobrepor a peça que está caindo
                if (ghost_x + x > player->x + 2)
                {
                    matriz[ghost_x + x][player->y + y] = ' ';
                }
            }
        }
    }
}

void points(void)
{
    attron(COLOR_PAIR(3));
    int8_t range_end = TAM_MAX_Y - 2;
    int8_t range_start = 2;
    int8_t count = 0;
    for (register int x = 0; x < TAM_MAX_X; x++)
    {
        count = 0;
        for (register int y = range_start; y < range_end; y++)
        {
            if (matriz[x][y] == 'X')
            {
                // mvprintw(x, (TAM_MAX_Y * 2) + y, "%c", matriz[x][y]);
                count++;

                if (count >= 25)
                {
                    // mvprintw(x, (TAM_MAX_Y * 3), "%d", count);

                    for (register int linha = x; linha > 1; linha--)
                        for (register int coluna = range_start; coluna < range_end; coluna++)
                        {
                            // mvprintw(linha, (TAM_MAX_Y * 4) + coluna, "%c", matriz[linha][coluna]);
                            if (matriz[linha - 1][coluna] != '=')
                            {
                                matriz[linha][coluna] = matriz[linha - 1][coluna];
                            }
                        }
                    point += 5;
                }
            }
        }
    }

    mvprintw(TAM_MAX_X + 1, 1, "Pontos: %li", point);
    attron(COLOR_PAIR(3));
}

void menu(void)
{
    initscr(); // inicializa a biblioteca

    start_color(); // inicializa as cores
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    bkgd(COLOR_PAIR(1));

    curs_set(0);
    keypad(stdscr, TRUE);
    noecho();
    timeout(100);

    for (int a = 0; a < TAM_MAX_X * 2; a++)
    {
        for (int b = 0; b < TAM_MAX_Y * 2; b++)
        {
            mvprintw(a, b, " ");
        }
    }

    char *select[3] = {"INICIAR", "OPCOES", " EXIT"};
    int8_t len = TAM_ARRAY(select);
    int8_t destaque = 0;
    int16_t prox = 1;

    for (int a = 0; a < 21; a++)
    {
        for (int b = 0; b < 60; b++)
        {
            if (a == 0 || a == 20 || b == 0 || b == 59)
                mvprintw(a, b, "*");
        }
    }

    attron(COLOR_PAIR(2));

    while (prox)
    {

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
            destaque = (destaque - 1 + len) % len;
            break;

        case KEY_DOWN:
            destaque = (destaque + 1) % len;
            break;

        case 10:
            if (destaque == len - 1)
            {
                sair();
            }
            else if (destaque == len - 3)
            {
                prox = !prox;
            }
            break;

        default:
            break;
        }
    }
    for (int a = 0; a < 21; a++)
    {
        for (int b = 0; b < 60; b++)
        {
            mvprintw(a, b, " ");
        }
    }
    endwin(); // finaliza a bibliotec
}