/*
 * Filename: debug2.c
 * Description: Runs the program for the game tic tac toe
 */
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "debug2.h"

/*
 * Function name: main 
 * Function prototype: int main()
 * Description: driver for running the program for tic tac toe game
 * Parameters: None
 * Side Effects: None
 * Error Conditions: None
 * Return Value: EXIT_SUCCESS
 */
int main(){
  /* Initialize game board */
  long board[3][3] = {{0}};

  /* Buffer for reading input */
  char buffer[BUFSIZ];

  /* Whose turn it is */
  long turn = 1;

  /* Longs ints to store the indicies */
  long * xIndex = calloc(1,sizeof(long));
  long * yIndex = calloc(1,sizeof(long));

  /* Number of moves to find a tie */
  long moves = 0;

  /* Print the initial board */
  printBoard(board);  

  while(turn) {    /* Run forever */
    /* Print input prompt */
    (void) printf("Player %ld, please enter your move: ", turn );

    /* End game if EOF is passed in */
    if(fgets(buffer, BUFSIZ, stdin) == NULL){
      break;
    }

    (void) printf("\n");
    
    /* Parse the x and y indicies */
    if(parsePlay(board, buffer, xIndex, yIndex)) {
      moves++;

      /* Initiate the move */
      board[*xIndex][*yIndex] = turn;

      /* Print the new board */
      printBoard(board);

      /* Check if a player won */
      if(checkWin( *xIndex, *yIndex, turn ) ) {
        (void) printf("Player %ld Won!\n", turn);
        break;
      }

      /* Check for a tie */
      if(moves == 9){
        (void) printf("It's a tie!\n");
        break;
      }

      /* Switch turns */
      turn = ((turn == 1) ? 2 : 1);
    }
  }
  free(xIndex);
  free(yIndex);
  return EXIT_SUCCESS;

}
