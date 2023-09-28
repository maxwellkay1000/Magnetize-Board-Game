#include <stdio.h>
#include <stdlib.h>
#include "logic.h"

game* new_game(unsigned int square, unsigned int maglock, unsigned int width,
               unsigned int height, enum type type){

    if(square <= 1){
        fprintf(stderr, "new_game was passed a value for square that is too small!");
        exit(1);
    }

    if(square > width || square > height){
        fprintf(stderr, 
            "new_game was passed a value for square that is too large based on the board!");
        exit(1);
    }

    game* res = (game*)malloc(sizeof(game));

    if(res == NULL){
        fprintf(stderr, "unable to allocate game!");
        exit(1);
    }
    
    res->square = square;
    res->maglock = maglock; 
    res->black_rem = 0;
    res->white_rem = 0;
    res->player = BLACKS_TURN; 
    res->b = board_new(width, height, type);

    return res;
}

void game_free(game* g){

    board_free(g->b);
    free(g); 
}

bool drop_piece(game* g, unsigned int column){

    // case where column is full already
    if(board_get(g->b, make_pos(0, column)) != EMPTY){
        return false; 
    }

    cell cell_set;
    if(g->player == WHITES_TURN){
        cell_set = WHITE;
    } else{
        cell_set = BLACK; 
    }

    // Case where pieces already in column
    for(unsigned int r = 1; r < g->b->height; r++){
        pos p2 = make_pos(r, column);
        if(board_get(g->b, p2) != EMPTY){
            pos p_set = make_pos(r - 1, column);
            board_set(g->b, p_set, cell_set);
            switch_turn(g);
            return true;
        }
    }

    // Case where no pieces in column yet
    pos p_set = make_pos(g->b->height - 1, column);
    board_set(g->b, p_set, cell_set);
    switch_turn(g);
    return true;

}

void start_maglock(game* g){

    if(g->player == BLACKS_TURN){
        g->black_rem = g->maglock; 
    }
    else{
        g->white_rem = g->maglock; 
    }
}


void switch_turn(game* g){

    if(g->black_rem > g->maglock || g->white_rem > g->maglock){
        fprintf(stderr, "black_rem or white_rem have a value greater than maglock!");
        exit(1);
    }

    //increment turn based on maglock 
    if(g->player == WHITES_TURN){
        if(g->black_rem > 0){
            g->black_rem--;
            if(g->black_rem == 0){
                gravity(g, BLACK);
            }
            return; 
        }
        else{
            g->player = BLACKS_TURN; 
        }
    }
    else if(g->player == BLACKS_TURN){
        if(g->white_rem > 0){
            g->white_rem--;
            if(g->black_rem == 0){
                gravity(g, WHITE);
            }
            return; 
        }
        else{
            g->player = WHITES_TURN;
        }
    }
}

//magnetize to the right only for now
bool magnetize(game* g){

    if(g->player == WHITES_TURN){
        while(magnetize_right(g)){
            gravity(g, BLACK);
        }

        start_maglock(g); 
        switch_turn(g);
        return true; 
    }   
    else if(g->player == BLACKS_TURN){
        while(magnetize_left(g)){
            gravity(g, WHITE);
        }
        
        start_maglock(g);
        switch_turn(g);
        return true; 
    }
    return false; 
}

//move every piece of a given color down 
bool gravity(game* g, cell color){

    bool success = false;

    for(int r = g->b->height - 1; r > -1; r--){
        for(int c = 0; c < g->b->width; c++){
            if(board_get(g->b, make_pos(r, c)) == color){
                if(shift_down(g, make_pos(r, c))){
                    success = true; 
                } 
            } 
        }
    }
    return success;
} 

outcome game_outcome(game* g){

    bool white_has_square = false;
    bool black_has_square = false; 

    for(int c = 0; c < g->b->width - g->square + 1; c++){
        for(int r = 0; r < g->b->height - g->square + 1; r++){
            pos current_p = make_pos(r, c);
            cell current_cell = board_get(g->b, current_p);
            if(current_cell != EMPTY){
                if(square_check(g, current_p, current_cell)){
                    if(current_cell == BLACK){
                        black_has_square = true; 
                    }
                    else{
                        white_has_square = true; 
                    }
                }
            }
        }
    }

    if(white_has_square && black_has_square){
        return DRAW;
    }
    else if(white_has_square){
        return WHITE_WIN;
    }
    else if(black_has_square){
        return BLACK_WIN; 
    }
    if(board_is_full(g)){
        return DRAW;
    }
    return IN_PROGRESS; 
}

bool board_is_full(game *g){

    for(int c = 0; c < g->b->width; c++){
        for(int r = 0; r < g->b->height; r++){
            if(board_get(g->b, make_pos(r, c)) == EMPTY){
                return false; 
            }
        }
    }
    return true; 
}

bool square_check(game* g, pos p, cell color){

    if(p.c > g->b->width - g->square ||
        p.r > g->b->height - g->square){
        fprintf(stderr, 
               "square_check was passed pos that couldn't be a square!");
        exit(1);
    }

    for(int c = p.c; c < p.c + g->square; c++){
        for(int r = p.r; r < p.r + g->square; r++){
            if(board_get(g->b, make_pos(r, c)) != color){
                return false;
            }
        }
    }
    return true; 
}   

bool shift_down(game* g, pos p){

    for(int r = p.r + 1; r < g->b->height; r++){
        pos current_p = make_pos(r, p.c);
        if(board_get(g->b, current_p) != EMPTY){
            pos p_destination = make_pos(r - 1, p.c);
            return move_piece(g, p, p_destination);
        }
        else if(r == g->b->height - 1){
            pos p_destination = make_pos(r, p.c); // support hitting the edge
            return move_piece(g, p, p_destination);
        }
    }
    return false; 
}

bool magnetize_right(game* g){

    if(g->player != WHITES_TURN){
        fprintf(stderr,
        "magnetize_right was called when it was not white's turn!");
        exit(1); 
    }
    
    bool success = false;

    for(int r = g->b->height - 1; r > -1; r--){
        for(int c = g->b->width - 1; c > -1; c--){
            if(board_get(g->b, make_pos(r, c)) == WHITE){
                if(shift_right(g, make_pos(r, c))){
                    success = true; 
                }
            } 
        }
    }
    return success;
}

bool magnetize_left(game* g){

    if(g->player != BLACKS_TURN){
        fprintf(stderr,
        "magnetize_left was called when it was not black's turn!");
        exit(1); 
    }
    
    bool success = false;

    for(int r = g->b->height - 1; r > -1; r--){
        for(int c = 0; c < g->b->width; c++){
            if(board_get(g->b, make_pos(r, c)) == BLACK){
                if(shift_left(g, make_pos(r, c))){
                    success = true;
                }
            }
        }
    }
    return success; 
}

/* shift piece on board over to the right*/
bool shift_right(game* g, pos p){

    if(p.c == g->b->width - 1){
        return false; 
    }

    for(int c = p.c + 1; c < g->b->width; c++){
        pos current_p = make_pos(p.r, c);
        if(board_get(g->b, current_p) != EMPTY){
            pos p_destination = make_pos(p.r, c - 1); 
            return move_piece(g, p, p_destination);
        }
        else if(c == g->b->width - 1){
            pos p_destination = make_pos(p.r, c); 
            return move_piece(g, p, p_destination);
        }
    }
    return false; 
}

bool shift_left(game *g, pos p){

    //case where piece is already on edge
    if(p.c == 0){
        return false; 
    }

    for(int c = p.c - 1; c > -1; c--){
        pos current_p = make_pos(p.r, c);
        if(board_get(g->b, current_p) != EMPTY){
            pos p_destination = make_pos(p.r, c + 1); 
            return move_piece(g, p, p_destination);
        }
        else if(c == 0){
            pos p_destination = make_pos(p.r, c); 
            return move_piece(g, p, p_destination);
        }
    }
    return false; 
}


bool move_piece(game* g, pos start, pos destination){

    if(start.r == destination.r && start.c == destination.c){
        return false; 
    }
    if (board_get(g->b, start) == EMPTY){
        return false;
    }
    if (board_get(g->b, destination) != EMPTY){
        return false; 
    }

    cell color = board_get(g->b, start);
    board_set(g->b, start, EMPTY);
    board_set(g->b, destination, color);

    return true; 
}

