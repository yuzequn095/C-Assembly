/*
 * Filename: printBoard.c
 * Description: Print out the tic tac toe board
 */
#define DIVIDER "-------\n"
#include <stdio.h>

/*
 * Function name: printBoard 
 * Function prototype: void printBoard( long board[] [3]);
 * Description: print out the current board
 * Parameters: 
 *      arg 1 - board - the board players are playing on
 * Side Effects: NONE
 * Error Conditions: NONE
 * Return Value: NONE
 *
 */
void printBoard( long board[][3] ){
  int row, col;

  (void) printf(DIVIDER);

  /* Loop rows */
  for(row = 0; row < 3; row++){
    (void) printf("%c", '|');

    /* Loop through columns */
    for(col = 0; col < 3; col++){
      if(board[row][col] == 0)
        (void) printf("%c", ' ');

      if(board[row][col] == 1)
        (void) printf("%c", 'X');

      if(board[row][col] == 2)
        (void) printf("%c", 'O');

      (void) printf("%c", '|');
    }

    (void) printf("%c", '\n');
    (void) printf(DIVIDER);
  }

}
