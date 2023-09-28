#ifndef LOGIC_H
#define LOGIC_H

#include <stdbool.h>
#include "board.h"


enum turn {
    BLACKS_TURN,
    WHITES_TURN
};

typedef enum turn turn;


enum outcome {
    IN_PROGRESS,
    BLACK_WIN,
    WHITE_WIN,
    DRAW
};

typedef enum outcome outcome;


struct game {
    unsigned int square, maglock, black_rem, white_rem;
    board* b;
    turn player;
};

typedef struct game game;

/* 
Allocate and return a new game stuct. Uses a matrix representation or a 
bit representation depending on the type argument. 
 */
game* new_game(unsigned int square, unsigned int maglock, unsigned int width,
               unsigned int height, enum type type);

/* Free a game stuct */
void game_free(game* g);

/* 
Drop a piece onto board of the appropriate color depending on which player's 
turn it is. Returns true if a piece has been dropped in the column and 
false if the move is impossible. Advances the player turn, accounting for 
maglock if it is active. 
*/
bool drop_piece(game* g, unsigned int column);

/*
Pulls all of black's pieces to the left or all of white's pieces to the 
right for a number of turns depending on whose turn it is, and holds
them there for a number (maglock) of turns. 
*/
bool magnetize(game* g);


/* 
Determines the game outcome. If black has a sqaure of the specified size
black wins. White wins if they have a square. Game is drawn if both players
make a square in the same turn. Game is drawn if the board is full and 
neither player has a square. Returns an enum for the outcome. 
*/
outcome game_outcome(game* g);

/* 
Moves a piece from pos start to pos destination, returns true if possible
and false otherwise.
*/
bool move_piece(game* g, pos start, pos destination); 

/* 
Shifts a single piece on the board as far as possible to the right.
Returns true if the piece moved and false if it can't move to the right. 
*/
bool shift_right(game* g, pos p);

/* 
Shifts a single piece on the board as far as possible to the left 
Returns true if the piece moved and false if it can't move to the left. 
*/
bool shift_left(game *g, pos p);

/* 
Shifts a single piece on the board as far as possible downard.  
Returns true if the piece moved and false if it can't move down. 
*/
bool shift_down(game* g, pos p); 

/* 
Magnetizes white pieces to the right of the board.  
*/
bool magnetize_right(game* g);

/* 
Magnetizes white pieces to the left of the board.  
*/
bool magnetize_left(game* g);

/* 
Applies gravity to the board, causing all pieces to move downward as far as
possible. 
*/
bool gravity(game*g, cell color);

/*
Checks if a pos p is the top left corner of a winning sqaue of a specified 
color
*/
bool square_check(game* g, pos p, cell color);

/*
Returns true if the board is entirely full and false otherwise. 
*/
bool board_is_full(game *g); 

/* Switches turn in game struct, accounting for the maglock mechanic */ 
void switch_turn(game* g);


#endif /* LOGIC_H */
