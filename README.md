# Magnetize-Board-Game
Implements a board game called *Magnetize* in C. 

## How the Game Works
Magnetize is a board game for two players that involves black and white pieces on a rectangular grid; unlike many board games, the board stands up vertically. The objective is to form a square of pieces of your color. Players take turns dropping pieces in chosen columns in the board, where they fall to the lowest possible level. Players can also temporarily turn on a magnet," causing all their pieces to slide as far to the left or right as possible within their rows, and then to cling for some number of turns before falling downwards if they are unsupported. This dynamic gives the game an unexpected dimension and offers the potential to surprise your opponent. 

To sum up the gameplay: players take alternating turns. In a turn, a given player either drops one piece in any non-full column, dropping it as low as it can go, or turns on their magnet. Magnets only slide pieces of one color, and only in that color's direction (right for white, left for black). Pieces defy gravity while the magnet is on, but eventually drop after the magnet turns off. The Maglock interval defines for how long they stay on, and this interval is the number of turns, after the one in which the magnet is turned on, the player loses as a result. It is at the end of that player's last missed turn that their pieces fall. Opponent pieces held up by those pieces would also fall at this time. The Maglock interval in the depicted game was 2. The objective of the game is to get a number of pieces of your color in a square of a configured dimension, here 2.

If the board becomes full without a winning condition for either player, then the game is declared a draw. If both players were to happen to get squares at the same time, then the game is also a draw (even if one player happens to have more, or larger, such squares than the other).

One additional note about the effects of a magnet: There can be a cascading effect where the magnet moves one color's pieces, then the opponent's pieces fall; this may free up some of the magnetized player's pieces to move further, which could result in further opponent falls, and so on. 

## About this Project


### Play.c

This file contains the main gameplay loop. 

The play executable requires command-line arguments: -h 3 -w 4 -s 2 -l 5, specifying (in the order shown) the height, width, winning square size, and Maglock interval that should be passed in to new_game. The user can specify any valid values on the command line, and in any order. There are no defaults.

### Bits Representation of the Game Board

The board is scanned from top to bottom, with individual rows scanned from left to right: in other words, in the same manner in which English text is read and written. In this order, the bits are placed in a one-dimensional array.

The first 32 bits are placed in the first element of this array. The first two bits, representing the top-left corner of the board, are the two least-significant bits (the two with the smallest place values) in this first array entry. Subsequent cells use higher-valued bits. Once the first array entry is used up, we move on to the next, again beginning with that entry's least-significant bits. We allocate precisely as few array elements as are needed for the desired board size. Depending upon the size of the board, the last array element may only be partially used; if so, the higher-value bits of that element will be unused. 





