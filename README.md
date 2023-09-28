# Magnetize-Board-Game
Implements a complex, text-based board game called *Magnetize* in C. 

## How the Game Works
Magnetize is a board game for two players that involves black and white pieces on a rectangular grid; unlike many board games, the board stands up vertically. The objective is to form a square of pieces of your color. Players take turns dropping pieces in chosen columns in the board, where they fall to the lowest possible level. Players can also temporarily turn on a magnet," causing all their pieces to slide as far to the left or right as possible within their rows, and then to cling for some number of turns before falling downwards if they are unsupported. This dynamic gives the game an unexpected dimension and offers the potential to surprise your opponent. 

Magnetize is played with pieces on a rectangular board. There is a grid consisting of rows and columns, each cell of which can be empty, hold a black piece, or hold a white piece. The numbers of rows and columns are configurable.) Players take turns, starting with black, then white, then black, and so on. In some cases, a player's turn is skipped. We will show examples in the format that your program will display boards to screen.

	01234

	0 .....
	1 .....
	2 .....
	3 .....

This is a board with four rows and five columns, empty at the start of the game. Empty spaces are depicted with period (.) characters.

Black moves first. They drop a black piece (which will be drawn as an asterisk, into column 1 (using zero-based indexing). Because the board is standing up, the piece falls down to the bottom of this column:

	01234

	0 .....
	1 .....
	2 .....
	3 .*...

 White moves next, and drops a piece in column 3. White's pieces will be depicted using the lower-case letter o (as in Oscar). This piece also falls to the bottom.

	01234

	0 .....
	1 .....
	2 .....
	3 .*.o.

Black moves next, in column 0.


	01234

	0 .....
	1 .....
	2 .....
	3 **.o.

This piece falls to the bottom of its column as well.


Sensing that black is starting to build a square, white drops a piece in column 1 to block its formation.

	01234

	0 .....
	1 .....
	2 .o...
	3 **.o.

The piece falls as far down as it can go, but rests above the piece already in the column.

Black uses their turn to drop a further piece in this column.

	01234

	0 .....
	1 .*...
	2 .o...
	3 **.o.

White next drops a piece in column 4.

	01234

	0 .....
	1 .*...
	2 .o...
	3 **.oo

Black, sensing an incipient white square, drops a piece in column 3.


	01234

	0 .....
	1 .*.o.
	2 .o.*.
	3 **.oo


Black does the same.


	01234

	0 ...*.
	1 .*.o.
	2 .o.*.
	3 **.oo

 
Instead of dropping a piece this turn, white now decides to turn on their magnet. White's magnet is on the right, and black's magnet is on the left. The result is that white's pieces are pulled as far to the right as they can go, while black's pieces remain immobile. White's pieces will either be pinned against the right wall, or against a black piece.

	01234

	0 .....
	1 ...*o
	2 .*o*.
	3 **.oo

Notice that white's piece in row 1 moved all the way to the right wall. But, white's piece in row 2 only moved one spot closer to the wall, as it was blocked from reaching the wall by black's piece. There were also two white pieces in the bottom row. However, they were bunched up as close to the wall as they could get, so the magnet had no effect on them.


Further, notice that both of the white pieces that moved are now hanging in the air, defying gravity. The magnet remains on for some period of time, and is strong enough to keep the pieces it attracts from falling downward until it turns off.


Notice also, however, that black pieces that were above the white pieces that slid have now fallen. The magnet does not directly affect black pieces, so once the cell(s) below them becomes empty, they may fall.


To be clear, the properties of turning on a magnet are precisely defined: all the pieces of the specific color stay within their row and move as far as they can in the appropriate direction, with no falling. After this transformation has been completed, then, gravity takes effect, and any unsupported pieces belonging to the other color fall downwards.


Continuing with this particular game, black drops a piece in column 2.

	01234

	0 .....
	1 ..**o
	2 .*o*.
	3 **.oo

Then black drops a piece in column 4. What happened to white's turn? When a player turns on a magnet, it stays on for the Maglock interval; this represents how many turns the player loses while the magnet remains on. So, in this game, the Maglock interval happens to be long enough that white misses a couple of turns and black can play repeatedly. This is in recognition of the fact that turning on a magnet is a potentially powerful move and should have somme disadvantage to balance against it.


Here is the result after black drops that piece in column 4. White's pieces continue to hover because the magnet is still on. Once the Maglock interval is over, they will drop according to gravity and white will regain their ability to take turns.

	01234

	0 .....
	1 ...**
	2 .***o
	3 **ooo

This board shows the result of black's drop in column 4 and also the final forfeit turn of white, as the magnet has now turned off and white's pieces have dropped. But since this turn was also forfeit, black can go another time. Black uses the opportunity to turn on their magnet, which, recall, pulls to the left.

	01234

	0 .....
	1 **...
	2 ***.o
	3 **ooo

In so doing, black has accumulated a 2x2 square. The configuration of this particular game is such that this is the condition to win. Black wins.

The game is made interesting because the consequences of sliding and falling can be subtle, and hard for an opponent to recognize soon enough to interdict.

To sum up the gameplay: players take alternating turns. In a turn, a given player either drops one piece in any non-full column, dropping it as low as it can go, or turns on their magnet. Magnets only slide pieces of one color, and only in that color's direction (right for white, left for black). Pieces defy gravity while the magnet is on, but eventually drop after the magnet turns off. The Maglock interval defines for how long they stay on, and this interval is the number of turns, after the one in which the magnet is turned on, the player loses as a result. It is at the end of that player's last missed turn that their pieces fall. Opponent pieces held up by those pieces would also fall at this time. The Maglock interval in the depicted game was 2. The objective of the game is to get a number of pieces of your color in a square of a configured dimension, here 2.

If the board becomes full without a winning condition for either player, then the game is declared a draw. If both players were to happen to get squares at the same time, then the game is also a draw (even if one player happens to have more, or larger, such squares than the other).

One additional note about the effects of a magnet: There can be a cascading effect where the magnet moves one color's pieces, then the opponent's pieces fall; this may free up some of the magnetized player's pieces to move further, which could result in further opponent falls, and so on. 

## About this Project

### Structure 

- pos.h and pos.c: implement a struct to hold coordinates on the game board

- board.h and board.c: maintain and manipulate the state of the board (information about what pieces are where)

- logic.h and logic.c: implement the rules of the game

- evidence.c: provides unit tests for the functions in this assignment

- Makefile: builds an executable named evidence that runs the unit tests




### Play.c

This file contains the main gameplay loop. 

The play executable requires command-line arguments: -h 3 -w 4 -s 2 -l 5, specifying (in the order shown) the height, width, winning square size, and Maglock interval that should be passed in to new_game. The user can specify any valid values on the command line, and in any order. There are no defaults.

### Bits Representation of the Game Board

The board is scanned from top to bottom, with individual rows scanned from left to right: in other words, in the same manner in which English text is read and written. In this order, the bits are placed in a one-dimensional array.

The first 32 bits are placed in the first element of this array. The first two bits, representing the top-left corner of the board, are the two least-significant bits (the two with the smallest place values) in this first array entry. Subsequent cells use higher-valued bits. Once the first array entry is used up, we move on to the next, again beginning with that entry's least-significant bits. We allocate precisely as few array elements as are needed for the desired board size. Depending upon the size of the board, the last array element may only be partially used; if so, the higher-value bits of that element will be unused. 





