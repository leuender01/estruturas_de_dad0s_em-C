#ifndef TETRIS
#define TETRIS 
#include <inttypes.h>

enum TELA{
    X= 15,
    Y= 15
};

typedef struct{
    char *cor;
    int8_t x;
    int8_t y;
}Bloco;

#endif