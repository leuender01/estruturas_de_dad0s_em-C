#ifndef TETRIS
#define TETRIS 

#define TAM_MAX_X 51
#define TAM_MAX_Y 30


#include <stdbool.h>

typedef struct quadrado{
    int x;
    int y;
    int type;
    int rotate;
    char blocos[3][3];
}PLAYER;

typedef struct {
    char forma[4][3][3];
    int max_rot;
}MODELO;

char matriz[TAM_MAX_X][TAM_MAX_Y] = {0};

void table(void);
void sair(void);
void inicializador(PLAYER *player);
void Player(PLAYER *player);
void escolher(PLAYER *player);
bool colision(PLAYER *player, int index , int indey);
void rotate(PLAYER *player);
void Previw(PLAYER * player);
void tetris_previw(PLAYER *player);
void clear_tetris(PLAYER *player);
void tetris_clear(PLAYER *player);

#endif