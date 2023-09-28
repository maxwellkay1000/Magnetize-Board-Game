#ifndef POS_H
#define POS_H

struct pos {
    unsigned int r, c;
};

typedef struct pos pos;

/* Return a new pos struct */
pos make_pos(unsigned int r, unsigned int c);

#endif /* POS_H */

