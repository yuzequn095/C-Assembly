/*
 * Filename: parsePlay.c
 * Description: parse the moves enter by player
 */
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "debug2.h"

/*
 * Function name: parsePlay 
 * Function prototype: long parsePlay(long board[][3], char* input,
 *                                    long * xIndex, long * yIndex);
 * Description: reads the move inputted by the plaer and see if it is a valid
 *              move command
 * Parameters: 
 *      arg 1 - board - the board players are playing on
 *      arg 2 - input - the move string inputted by the player
 *      arg 3 - xIndex - the row index of that move
 *      arg 4 - yIndex - the col Index of that move
 * Side Effects: None
 * Error Conditions: The input string entered in not a valid move command
 * Return Value: 0 if error occurred, 1 if a play is valid
 */
long parsePlay( long board[][3], char * input, long * xIndex, long * yIndex ){
  
  char * begin;
  char * pos;
  char * endptr;

  begin = input;

  /* Search for left paren */
  pos = strchr(begin, '(');
  
  /* If the left paren is not the first character return 0 */
  if(pos != begin || pos == NULL){
    (void) fprintf(stderr, "Missing left paren\n");
    return 0;
  }

  /* Replace comma with nul char if present */
  pos = strchr(begin, ',');
  if(pos == NULL){
    (void) fprintf(stderr, "Missing middle comma\n");
    return 0;
  }
  *pos = '\0';

  /* Parse x index */
  errno = 0;
  *xIndex = strtol(++begin, &endptr, 10);
  if(*endptr  || errno != 0){
    (void) fprintf(stderr, "xIndex not a number\n");
    return 0;
  }

  /* Move past comma */
  begin = pos + 1;

  /* Find and replace right paren */
  pos = strchr(begin, ')');
  if(pos == NULL){
    (void) fprintf(stderr, "Missing right paren\n");
    return 0;
  }
  *pos = '\0';

  /* Parse y index */
  errno = 0;
  *yIndex = strtol(begin, &endptr, 10);
  if(*endptr || errno){
    (void) fprintf(stderr, "yIndex not a number\n");
    return 0;
  }

  /* Check for extra characters */
  if(*(pos + 1) != '\n'){
    (void) fprintf(stderr, "Extra characters after right paren\n");
    return 0;
  }

  /* Check if move is valid */
  if(!checkMove(board, *xIndex, *yIndex)){
    (void) fprintf(stderr, "Invalid position\n");
    return 0;
  }
  return 1;
}

