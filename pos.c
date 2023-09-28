#include <stdio.h>
#include <stdlib.h>
#include "pos.h"


pos make_pos(unsigned int r, unsigned int c){

    //pos res = (pos*)malloc(sizeof(pos));

    //CHECK IN OFFICE HOURS ON WED
    //if (res == NULL){
    //    fprintf(stderr, "make_pos allocated null pos struct");
    //    exit(1);
    //}

    pos res; 

    res.r = r;
    res.c = c;

    return res; 
}