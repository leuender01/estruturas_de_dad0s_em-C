#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ncurses.h>

#define TAM_MAX_X 30
#define TAM_MAX_Y 60
#define TAM_MAX_SNAKE TAM_MAX_X * TAM_MAX_Y

struct position{
    int x, y;
};

typedef struct {
    char skin;
    int length;
    struct position body[TAM_MAX_SNAKE];
} Player;

int directionx = 1, directiony = 0;

void add_body(Player *cobra, struct position *comida);
int8_t colisao(Player *cobra, struct position *comida);
void print_table(Player *cobra, struct position *comida);
Player inicializar(struct position *comida);
void mover(Player *cobra, int c);

int main(void)
{    
    struct position comida;
    Player cobra = inicializar(&comida);
    while(1)
    {
        print_table(&cobra, &comida);
        int c = getch();
        if(c == 'q' || c == 'Q') break;
        else if(colisao(&cobra, &comida)) break;
        else mover(&cobra, c);
        attron(COLOR_PAIR(2));
        mvprintw(TAM_MAX_X + 2, 0, "cobra[ x: %d, y: %d length: %d]", cobra.body[0].x, cobra.body[0].y, cobra.length);
        mvprintw(TAM_MAX_X + 3, 0, "comida[ x: %d, y: %d]", comida.x, comida.y);
        attroff(COLOR_PAIR(2));
        refresh();
    }
    endwin();
    return 0;
}

void print_table(Player *cobra, struct position *comida)
{
    for ( int x = 1; x < TAM_MAX_X; x++)
    {
        for ( int y = 1; y < TAM_MAX_Y; y++)
        {
            mvprintw(x, y, "%c", ' ');
        }
    }

    for ( int x = 0; x < TAM_MAX_X; x++)
    {
        for ( int y = 0; y < TAM_MAX_Y; y++)
        {
            if(x == (TAM_MAX_X - 1) || y == (TAM_MAX_Y - 1) || x == 0 || y == 0){ 
                attron(COLOR_PAIR(2));
                mvprintw(x, y, "%c", '#');
                attroff(COLOR_PAIR(2));
            }
            for( int i = 0; i < cobra->length; i++){
                if(x == cobra->body[i].x && y == cobra->body[i].y){
                    attron(COLOR_PAIR(3));
                    mvprintw(x, y, "%c", cobra->skin);
                    attroff(COLOR_PAIR(3));
                }
            }
            if(x == comida->x && y == comida->y){

                attron(COLOR_PAIR(4));
                mvprintw(x, y, "%c", 'G');
                attroff(COLOR_PAIR(4));
            }
        }
    }
}

Player inicializar(struct position *comida)
{
    initscr();
    noecho();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_BLACK); 
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);   
    bkgd(COLOR_PAIR(1));
    curs_set(0);
    srand(time(NULL));
    keypad(stdscr, TRUE);
    timeout(250);
    Player cobra;
    struct position body;
    cobra.skin = '@';
    cobra.length = 1;
    body.x = TAM_MAX_X / 2;
    body.y = TAM_MAX_Y /2;
    comida->x = rand() % (TAM_MAX_X - 5) + 1;
    comida->y = rand() % (TAM_MAX_Y - 5)+ 1;
    cobra.body[0] = body;
    return cobra;
}

void mover(Player *cobra, int c)
{
    switch(c){
        case KEY_UP:
            directionx = -1;
            directiony = 0;
        break;
        case KEY_DOWN:
            directionx = 1;
            directiony = 0;
        break;
        case KEY_LEFT:
            directionx = 0;
            directiony = -1;
        break;
        case KEY_RIGHT:
            directionx = 0;
            directiony = 1;
        break;
    }

    for( int i = cobra->length - 1; i > 0; i--){
        cobra->body[i] = cobra->body[i - 1];
    }
    cobra->body[0].x += directionx;
    cobra->body[0].y += directiony;
}

int8_t colisao(Player *cobra, struct position *comida)
{
    if(cobra->body[0].x >= (TAM_MAX_X - 1) || cobra->body[0].y >= (TAM_MAX_Y - 1) || cobra->body[0].x <= 0 || cobra->body[0].y <= 0){
        return 1;
    }
    if(cobra->length > 1){
        for(int i = 1; i < cobra->length; i++){
            if(cobra->body[i].x == cobra->body[0].x && cobra->body[i].y == cobra->body[0].y) return 1;
            }
        }
    if(cobra->body[0].x == comida->x && cobra->body[0].y == comida->y) add_body(cobra, comida);
    return 0;
}

void add_body(Player *cobra, struct position *comida)
{
    srand(time(NULL));
    comida->x = rand() % (TAM_MAX_X - 5) + 1;
    comida->y = rand() % (TAM_MAX_Y - 5)+ 1;
    if(cobra->length >= TAM_MAX_SNAKE) return;
    struct position newsegment;
    newsegment.x = cobra->body[cobra->length - 1].x + (-directionx);
    newsegment.y = cobra->body[cobra->length - 1].y + (-directiony);
    cobra->body[cobra->length] = newsegment;
    cobra->length += 1;
}
