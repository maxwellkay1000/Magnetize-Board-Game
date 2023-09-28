#include <stdio.h>
#include <stdlib.h>
#include "board.h"


board* board_new(unsigned int width, unsigned int height, enum type type){

    board* res = (board*)malloc(sizeof(board));
    if(res == NULL){
        fprintf(stderr, "board_new unable to allocate board!");
        exit(1);
    }
    res->width = width;
    res->height = height; 
    res->type = type; 

    if(type == MATRIX){

        if(width < 2 || height < 2){
            fprintf(stderr, 
                "board_new was passed parameters for a board that is too small!");
        }

        enum cell** m = (cell**)malloc(height * sizeof(cell*));
        if(m == NULL){
            fprintf(stderr, "board_new unable to allocate matrix of cells!");
            exit(1);
        }
        for(int i = 0; i < height; i++){
            m[i] = (cell*)malloc(width * sizeof(cell));
            if(m[i] == NULL){
                fprintf(stderr, "board_new unable to allocate cell array!");
                exit(1);
            }
            for(int j = 0; j < width; j++)
            m[i][j] = EMPTY;
        }

        res->u.matrix = m; 
    }
    else if(type == BITS){
        
        unsigned int num_cells = width * height; 
        unsigned int num_elements;
        if(num_cells % 16 == 0){
            num_elements = num_cells / 2;
        }
        else{
            num_elements = num_cells / 2 + 1; 
        }

        unsigned int* bits = 
            (unsigned int*)malloc(num_elements * sizeof(unsigned int));
        if(bits == NULL){
            fprintf(stderr, "Couldn't allocate bit board!");
            exit(1);
        }
        for(unsigned int i = 0; i < num_elements; i++){
            bits[i] = 0x0; 
        }
        
        res->u.bits = bits;
    }
    return res; 
}

void board_free(board* b){

    if(b->type == BITS){
        free(b->u.bits);
    }
    else{
        for(int i = 0; i < b->height; i++){
            free(b->u.matrix[i]);
        }
        free(b->u.matrix); 
    }
    free(b); 
}

char get_label(unsigned int i){
    
    if(i >= 36){
        return i + 'a' - 36; 
    }
    else if(i >= 10){
        return i + 'A' - 10; 
    }
    else if(i < 10){
        return '0' + i; 
    }
    else{
        return '?'; 
    }
}

void board_show(board* b){

    for(unsigned int r = 0; r < b->height + 2; r++){ 
        for (unsigned int c = 0; c < b->width + 2; c++){  
            if(r < 2 && c < 2){
                printf(" ");
                continue;
            } 
            if(r == 0){
                printf("%c", get_label(c - 2));
                continue; 
            }
            else if(c == 0){
                printf("%c", get_label(r - 2));
                continue;
            }
            if(c == 1 || r == 1){
                printf(" ");
            }
            else if(board_get(b, make_pos(r - 2, c - 2)) == WHITE){  
                printf("o");
            }
            else if(board_get(b, make_pos(r - 2, c - 2)) == BLACK){
                printf("*");
            }
            else{
                printf(".");
            }
        }
        printf("\n");
    }
}

cell board_get(board* b, pos p){

    if(p.r > b->height - 1){ 
        fprintf(stderr, 
            "board_get was passed a position with row out of bounds: %d!\n", p.r);
        exit(1);
    }
    if(p.c > b->width - 1){
        fprintf(stderr, 
            "board_get was passed a position with col out of bounds: %d!\n", p.c);
        exit(1);
    }
    cell res; 
    if(b->type == MATRIX){
        res = b->u.matrix[p.r][p.c]; 
    }
    else{
        int bit_position = (p.r * b->width + p.c) * 2;
        int pos_in_arr = bit_position % 32; 
        int array_index = (bit_position / 32); 
        unsigned int mask = 0x3 << pos_in_arr; 
        unsigned int masked = b->u.bits[array_index] & mask;
        res = masked >> pos_in_arr; 
    }

    return res; 
}

void board_set(board* b, pos p, cell c){

    if(p.r > b->width - 1){
        fprintf(stderr, "board_set was passed a position with row out of bounds!");
        exit(1);
    }
    if(p.c > b->width - 1){
        fprintf(stderr, "board_set was passed a position with col out of bounds!");
        exit(1);
    }
    if(b->type == MATRIX){
        b->u.matrix[p.r][p.c] = c; 
    }
    else{
        int bit_position = (p.r * b->width + p.c) * 2;
        int array_index = bit_position / 32; 
        int pos_in_array = bit_position % 32;  
        unsigned int new_bits = c << pos_in_array; 
        unsigned int mask = 0x3 << pos_in_array;  
        b->u.bits[array_index] = (b->u.bits[array_index] & ~mask) | new_bits;

    }
     
}
