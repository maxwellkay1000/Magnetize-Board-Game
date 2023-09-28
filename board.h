#ifndef BOARD_H
#define BOARD_H

#include "pos.h"


enum cell {
    EMPTY,
    BLACK,
    WHITE
};

typedef enum cell cell;


union board_rep {
    enum cell** matrix;
    unsigned int* bits;
};

typedef union board_rep board_rep;


enum type {
    MATRIX, BITS
};


struct board {
    unsigned int width, height;
    enum type type;
    board_rep u;
};

typedef struct board board;

/* Allocate a fully-empty board of the desired size and type */
board* board_new(unsigned int width, unsigned int height, enum type type);

/* free a board struct and its matrix */
void board_free(board* b);

/* print a representation of the board */
void board_show(board* b);

/* return the cell enum (color) of a position p on the board */
cell board_get(board* b, pos p);

/* set the color c of a position p on the board b */
void board_set(board* b, pos p, cell c);

/* returns the appropriate char for col or row label on the board */
char get_label(unsigned int i);


#endif /* BOARD_H */