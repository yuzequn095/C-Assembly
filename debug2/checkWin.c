/*
 * Filename: checkWin.c
 * Description: check if a player has won
 */
#include <stdlib.h>

/*
 * Function name: checkWin
 * Function prototype: long checkWin(long xIndex, long yIndex, long turn);
 * Description: check if a player has won by keeping track of player's moves
 *              on the board
 * Parameters: 
 *      arg 1 - xIndex - the row index of the player's move
 *      arg 2 - yIndex - the col index of the player's move
 *      arg 3 - turn - whose turn it was that made the move
 * Side Effects: None
 * Error Conditions: None
 * Return Value: 1 if a player won, 0 if not one has won yet
 *
 */
long checkWin( long xIndex, long yIndex, long turn ){
  /*
   * Arrays that hold the number of plays for each player
   * These arrays should retain the values from previous calls. 
   */
  static long xWinArray[3] = {0};
  static long yWinArray[3] = {0};
  static long dWinArray[2] = {0};

  /* If player is player 2, make its value -1 */
  if(turn == 2)
    turn = -1;
   
  /* Add the value and check if its equal to 3 or -3 */    
  if(abs(xWinArray[xIndex] += turn) == 3)
    return 1;
  
  if(abs(yWinArray[yIndex] += turn) == 3)
    return 1;

  if(!(xIndex - yIndex)) {
    if(abs(dWinArray[0] += turn) == 3)
      return 1;
  }

  if((xIndex + yIndex) == 2) {
    if(abs(dWinArray[1] += turn) == 3)
      return 1;
  }
  
  return 0;
}
