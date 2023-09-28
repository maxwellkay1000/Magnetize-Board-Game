#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "pos.h"
#include "logic.h"

/* 
Note to graders: 
Certain edge cases involving gravity for pieces do not work 
*/

/* Returns column # corresponding to input character */
int get_int(char ch){

    if(ch >= 48 && ch <= 57){
        return ch - 48; 
    }
    if(ch >= 65 && ch <= 90){
        return ch - 65; 
    }
    if(ch >= 97 && ch <= 122){
        return ch - 97;
    }
    else{
        fprintf(stderr, "get_int was passed invalid char!\n");
        exit(1); 
    }
}

int main(int argc, char *argv[]){

    unsigned int width, height, square, maglock; 

    for(unsigned int i = 1; i < argc; i += 2){

        if(argv[i][0] != '-' || argv[i][2] != '\0'){
            fprintf(stderr, "play was passed invalid args!\n"); 
            exit(1);
        }

        switch (argv[i][1]){
        case 'w':
            width = atoi(argv[i + 1]);
            break;
        case 'h':
            height = atoi(argv[i + 1]);
            break;
        case 's':
            square = atoi(argv[i + 1]);
            break;
        case 'l':
            maglock = atoi(argv[i + 1]);
            break;
        default:
            fprintf(stderr, "play was passed invalid args!"); 
            exit(1); 
        }
    }

    game* g = new_game(square, maglock, width, height, BITS);
    outcome o = IN_PROGRESS;
    board_show(g->b); 

    do {

        int drop_col = 0; 

        if(g->player == WHITES_TURN){
            printf("White: ");
        }
        else{
            printf("Black: ");
        }

        char ch;
        scanf("%c%*c", &ch); 
        
        // magnetize
        if (ch == '!'){
            magnetize(g);
            o = game_outcome(g);
            if(o != IN_PROGRESS){
                break;
            }
            else{
                board_show(g->b);
                continue; 
            }
        }

        // drop piece 
        if( (ch >= 48 && ch <= 57) ||
            (ch >= 65 && ch <= 90) ||
            (ch >= 97 && ch <= 122)){
                drop_col = get_int(ch);
        }
        else{
            printf("\n'%c' is Invalid Character\n", ch);
            continue; 
        }

        if(drop_piece(g, drop_col)){
        }
        else{
            printf("Couldn't drop piece there\n");
            continue; 
        }
        board_show(g->b); 
        o = game_outcome(g);

    } while(o == IN_PROGRESS); 

    board_show(g->b);
    if(o == DRAW){
        printf("Game is drawn!\n");
    }
    else if(o == WHITE_WIN){
        printf("White wins!\n");
    }
    else{
        printf("Black wins!\n");
    }
    return 0;    
    
}