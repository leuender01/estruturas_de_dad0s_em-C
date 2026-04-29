#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <ncurses.h>
#include <signal.h>
#include "tetris.h"
#include "cor.h"
#include "tetris.h"

char *matriz[X][Y];

void Table(void)
{
    for (int i = 0; i < X; i++)
        for (int j = 0; j < Y; j++)
            matriz[i][j] = BACK_BLACK "  " RESET;
    // matriz[X-1][Y-1] = RESET;
}

void printTable(void)
{
    for (int i = 0; i < X; i++)
    {
        for (int j = 0; j < Y; j++)
            printf("%s", matriz[i][j]);
        printf("\n\r");
    }
}

int main(void)
{

    int buffer = 0, fd[2];
    srand(time(NULL));
    Bloco bloco1 = {BACK_RED "     " RESET, 0, (rand() % Y - 1)};
    pipe(fd);
    Table();

    pid_t jogo = fork();
    // close(fd[1]);
    // close(fd[1]);
    // read(fd[0], &buffer, sizeof(buffer));
    
    if(jogo == 0){
        int c;
        system("clear");
        close(fd[1]);
        matriz[bloco1.x][bloco1.y] = bloco1.cor;
        //printTable();
        while(c != 'q')
        {
            read(fd[0], &c, sizeof(c));
            printTable();
            //printf("buffer: %d\r", c);
        }

        // strcpy(matriz[bloco1.x][bloco1.y], bloco1.cor);
        /*
            printTable();
            */
    }else{
        close(fd[0]);
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        nodelay(stdscr, TRUE);
        while ((buffer = getch()) != 'q')
        {
            write(fd[1], &buffer, sizeof(buffer));
            //printf("buffer: %d\n", buffer);
            //close(fd[1]);
            refresh();
        }
        kill(jogo, SIGKILL);
        endwin();
    }
    return 0;
}