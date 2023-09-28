#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "pos.h"
#include "logic.h"

/* test make_pos */
void evidence_make_pos(){
    printf("-------- Testing pos.c ----------\n");
    printf("*** Testing make_pos ***\n");
    pos p = make_pos(1, 1);
    printf("- Expecting 1, 1: %d, %d\n", p.r, p.c);
    pos p2 = make_pos(10, 4);
    printf("- Expecting 10, 4: %d, %d\n", p2.r, p2.c);
}

void evidence_game_outcome(enum type rep_type){

    printf("*** Testing game_outcome for Drawn games ***\n");

    game* g = new_game(2, 2, 5, 3, rep_type);
    drop_piece(g, 0);
    drop_piece(g, 2);
    drop_piece(g, 0);
    drop_piece(g, 2);
    drop_piece(g, 1);
    drop_piece(g, 3);
    drop_piece(g, 1);
    drop_piece(g, 3);
    board_show(g->b); 
    printf("- Expecting game_outcome to return DRAW (3) "
            "because both colors have 2x2 square: %d\n", 
            game_outcome(g));
    game_free(g);

    g = new_game(2, 2, 4, 2, rep_type);
    drop_piece(g, 0);
    drop_piece(g, 2);
    drop_piece(g, 2);
    drop_piece(g, 0);
    drop_piece(g, 1);
    drop_piece(g, 3);
    drop_piece(g, 3);
    drop_piece(g, 1);
    board_show(g->b); 
    printf("- Expecting game_outcome to return DRAW (3) "
            "because board is full: %d\n", 
            game_outcome(g));
    game_free(g);
}

void simulate_game(enum type rep_type){

    unsigned int rows = 4;
    unsigned int cols = 4;

    printf("-------- Testing logic.c ----------\n");
    printf("*** Testing new_game ***\n");

    game* g = new_game(2, 2, rows, cols, rep_type);

    printf("*** Testing drop_piece ***\n");
    drop_piece(g, 1);
    printf("- Expecting black piece at 3, 1\n");
    board_show(g->b);
    drop_piece(g, 1);
    drop_piece(g, 1);
    drop_piece(g, 1);
    printf("- Expecting... \n"
            "   - white piece at 2, 1\n" 
            "   - black piece at 1, 1\n"
            "   - white piece at 0, 1\n");
    board_show(g->b);
    printf("- Expecting false (0) for drop_piece in col 1 \n"
            "because dropping another piece in col 1 is impossible: %d\n",
            drop_piece(g, 1));
    printf(" - Expecting black piece in col 3\n");
    drop_piece(g, 3);
    board_show(g->b);

    printf("*** Testing magnetize ***\n");
    printf("- Expecting white pieces to Magnetize to the right "
            "and black pieces to fall down\n");
    magnetize(g);
    board_show(g->b); 
    printf("*** Testing Drop Piece and Demonstrating Maglock Support ***\n");
    drop_piece(g, 1);
    drop_piece(g, 2);
    printf("- Expecting two new black pieces in col 1 and col 2 "
            "because white's next 2 turns are skipped\n");
    board_show(g->b); 
    printf("- Expecting black pieces to magnetize to the left\n");
    magnetize(g);
    board_show(g->b); 

    drop_piece(g, 2);
    drop_piece(g, 2);
    printf("- Expecting two white pieces dropped into row 2 because black's "
            "maglock is on\n");
    printf("- Expecting two white pieces dropped into row 3 because black's "
            " maglock is still on\n");
    drop_piece(g, 3);
    board_show(g->b); 
    printf("*** Testing game_outcome ***\n"); 
    printf("- Expecting game_outcome to return WHITE_WIN (2) "
            "because white has 2x2 square: %d\n", 
            game_outcome(g));

    printf("*** Calling game_free ***\n"); 
    game_free(g); 
}


/* Tests for the functions in board.h */
void evidence_board(enum type rep_type){

    printf("-------- Testing board.c ----------\n");
    printf("*** Testing make_board ***\n");
    int rows = 20;
    int cols = 20;
    board* b = board_new(rows, cols, rep_type);

    printf("- Showing Empty 20x20 Board *** \n");
    board_show(b);
    printf("*** Testing board_free ***\n");
    printf("- Freeing Board\n");
    board_free(b);

    printf("*** Testing make_board Part 2 ***\n");
    rows = 4;
    cols = 4;
    b = board_new(rows, cols, rep_type);
    printf("showing empty bit board\n");
    board_show(b);
    printf("*** Testing Board Set ***\n");
    board_set(b, make_pos(1, 1), WHITE);
    board_set(b, make_pos(3, 3), WHITE);
    board_set(b, make_pos(2, 2), BLACK);
    board_set(b, make_pos(0, 0), WHITE);

    printf("Showing 4x4 Board with \n" 
                "-  white piece at 1, 1\n"
                "-  black piece at 3, 3\n"
                "- Black piece at 2, 2\n"
                "- white piece at 0,0 \n");
    board_show(b);

    printf("*** Testing board_get ***\n");
    printf("- Expecting 2: %d\n", board_get(b, make_pos(1, 1)));
    printf("- Expecting 1: %d\n", board_get(b, make_pos(2, 2)));
    printf("- Expecting 2: %d\n", board_get(b, make_pos(0, 0)));
    printf("- Freeing Board\n");
    board_free(b);
}


/* main: run the evidence functions above */
int main(int argc, char *argv[]){

    evidence_make_pos();
    evidence_board(BITS); 
    //simulate_game(BITS); 
    //evidence_game_outcome(BITS); 

    return 0;    
}