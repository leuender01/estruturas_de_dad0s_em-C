#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <ncurses.h>

#define MAX 100

const char decorations[6][22] =
{
    {' ',' ',' ','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','>'},    
    {' ',' ','#',' ',' ','*','*','*',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','>'},    
    {' ','#',' ',' ','*',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','>'},    
    {' ','#',' ',' ','*',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','>'},    
    {' ',' ','#',' ',' ','*','*','*',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','>'},    
    {' ',' ',' ','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','>'},    
};

struct cabeca 
{
    char *ports,
         *id,
         *image,
         *comand,
         *creat,
         *status,
         *names;
};

typedef struct cabeca * CONTAINERS[MAX]; 

void init(CONTAINERS lista, int *indice);
char *string(char buffer, char buf[128], int fd[2]); 
char *port(char buffer, char buf[128], int fd[2]);
void add(CONTAINERS lista, int *indice);
void freeC(CONTAINERS lista);
void inicializar(void);
void print(CONTAINERS lista, int *indice);
void limpar(void);

int main(void)
{
    CONTAINERS lista;
    int indice = 0;

    inicializar();
    
    while(1)
    {
        limpar();
        init(lista, &indice);
        add(lista, &indice);
        print(lista, &indice);
        refresh();
        freeC(lista);
        int c = getch();
        if(c == 27 || c == 'q' || c == 'Q') break;
    }

    endwin();

    return 0;
}
void limpar(void){

    for(int i = 0; i < 100 ; i++)
    {
        for(int j = 0; j <100; j++) mvprintw(i, j, "%s", " ");
    }
}
void print(CONTAINERS lista, int *indice)
{
    const char titulo[] = "|______________[CONTAINERS ATIVOS]__________________|\0";

    attron(A_BOLD);
    attron(COLOR_PAIR(2));   
    mvprintw(0 , 0, "%s", titulo);
    attroff(COLOR_PAIR(2)); 
    attroff(A_BOLD);
    
    int step = 0;
    for(int i = 0; i < (*indice); i++)
    {
        attron(A_BOLD);
        attron(COLOR_PAIR(3));

        mvprintw(7 + step+i , (strlen(titulo) / 2) - 1, "[%s]", lista[i]->id);
        mvprintw(4 + step+i , (strlen(titulo) / 2) - 1, "[%s]", lista[i]->comand);
        mvprintw(5 + step+i , (strlen(titulo) / 2) - 1, "{%s}", lista[i]->status);
        mvprintw(6 + step+i , (strlen(titulo) / 2) - 1, "[%s]", lista[i]->creat);

        attroff(COLOR_PAIR(3));
        attroff(A_BOLD);

        attron(A_BOLD);
        attron(COLOR_PAIR(4));

        mvprintw(2 + step+i , (strlen(titulo) / 2) - 1, "$%s", lista[i]->image);
        mvprintw(3 + step+i , (strlen(titulo) /2) - 1, "$%s", lista[i]->names);
        mvprintw(8 + step+i , strlen(titulo) - strlen(lista[i]->ports), "%s", lista[i]->ports); 

        attroff(COLOR_PAIR(4));
        attroff(A_BOLD);
        


        for(int j = 0; j < 6; j++){
            for(int a = 0; a < 22; a++){
                if(decorations[j][a] == ' ') attron(COLOR_PAIR(1));
                else if(decorations[j][a] == '*') attron(COLOR_PAIR(5));
                else if(decorations[j][a] == '#') attron(COLOR_PAIR(6));
                attron(A_BOLD);
                mvprintw(2 + step + i + j, 2 + a, "%c",decorations[j][a]);
               
                attroff(COLOR_PAIR(1));
                attroff(COLOR_PAIR(5));
            }
        }



        step+=7;
    }
}

void inicializar(void)
{
    initscr();
    
    start_color(); // inicializa as cores
    init_pair(1, COLOR_BLACK, COLOR_BLACK);  // Texto(Branco) | Fundo(Azul)
    init_pair(2, COLOR_CYAN, COLOR_BLACK); // Texto(Vermelho) | Fundo(Branco)
    init_pair(3, COLOR_GREEN, COLOR_BLACK);  // Texto(Azul) | Fundo(Branco)
    init_pair(4, COLOR_RED, COLOR_BLACK);   // Texto(Azul) | Fundo(Branco)
    init_pair(5, COLOR_WHITE, COLOR_BLACK);   // Texto(Azul) | Fundo(Branco)
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);   // Texto(Azul) | Fundo(Branco)
                                              //
    bkgd(COLOR_PAIR(1));
    noecho();
    curs_set(0);
    timeout(1000);
    keypad(stdscr, TRUE);
}

char *string(char buffer, char buf[128], int fd[2])
{
    int bytes_lidos;
    int i = 0;
    int cont_espaco = 0;
    char *image = NULL;
    while((bytes_lidos = read(fd[0], &buffer, 1)) > 0)
    {
        if(buffer != ' ' && buffer != '\n')
        {
            cont_espaco = 0;
            buf[i] = buffer;
            i++;
        }else if(buffer != '\n' && i > 0) cont_espaco++; 

        if((i > 0 && buffer == ' ' && cont_espaco > 1) || buffer == '\n' || cont_espaco > 2) break;
    }
    buf[i] = '\0';
    image = malloc(strlen(buf) + 1);
    strcpy(image, buf);
    return image;
}



void init(CONTAINERS lista, int *indice)
{
    *indice = 0;
    for(int i = 0; i < MAX ; i++)
    {
        lista[i] = NULL;
    }    
}

void add(CONTAINERS lista, int *indice)
{
    int fd[2];
    char buffer = '\0', buf[128];
    pid_t pid;
    

    pipe(fd);
    pid = fork();

    if(pid == 0)
    {

        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        execlp("docker", "docker", "ps", NULL);
    }else
    {
        close(fd[1]);
        int bytes_lidos;

        while((bytes_lidos = read(fd[0], &buffer, 1)) > 0) if(buffer == '\n') break;
        
        while((*indice) < MAX && (bytes_lidos = read(fd[0], &buffer, 1)) > 0)
        {
            struct cabeca *new = malloc(sizeof(struct cabeca));    
            new->id = port(buffer, buf, fd);
            
            new->image = string(buffer, buf, fd);
            new->comand = string(buffer, buf, fd);
            new->creat = string(buffer, buf, fd);
            new->status = string(buffer,buf , fd);
            new->ports = port(buffer, buf, fd);
            new->names = string(buffer, buf, fd);
            lista[*indice] = new;
            (*indice)++;
        }
       

        close(fd[0]);
        int status;
        wait(&status);
        
    }
   
}

char *port(char buffer, char buf[128],int fd[2])
{
    
    int bytes_lidos;
    int i = 0;
    int cont_espaco = 0;
    char *new = NULL;
    while((bytes_lidos = read(fd[0], &buffer, 1)) > 0)
    {
        if(buffer == ' ' ) cont_espaco++;
        else if(buffer != ' ' && buffer != '\n')
        {
            buf[i] = buffer;
            cont_espaco = 0;
            i++;
        }
        if(cont_espaco > 10 || (cont_espaco > 1 && i > 0 && buffer == ' ')) break;
        
    }
    buf[i] = '\0';
    new = malloc(strlen(buf) + 1);
    strcpy(new, buf);
    
    return new;
}

void freeC(CONTAINERS lista)
{
    int indice = 0;
    while(lista[indice] != NULL)
    {
        free(lista[indice]->ports);
        free(lista[indice]->id);
        free(lista[indice]->image);
        free(lista[indice]->comand);
        free(lista[indice]->creat);
        free(lista[indice]->status);
        free(lista[indice]->names);

        free(lista[indice]);

        indice++;
    }
}
