/*
 * Filename: main.c
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Jan 25th, 2019
 * Source of Help: Write up. DI slides.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include "pa1.h"
 #include "pa1Strings.h"
 #include "errno.h"
 #include <string.h>

 #define CONSTANT_TWO 2
 #define SEC_INDEX 2
 #define THI_INDEX 3
 #define END_CHAR '\0'
/*
  * Function Name: main()
  * Function Prototype: int main( int argc, char *argv[] );
  * Description: Drive the rest of the program. It will also  check errors.
  * Parameters: argc - number of command line arguments passed in
  *             argv - command line arguments passed in
  * Side Effects: Prints else information to stdout or stderr.
  * Error Condition: Wrong number of parameteres passed in or illegal params.
  * Return Value: EXIT_SUCCESS if no errors, otherwise EXIT_FAILURE.
  */
 int main( int argc, char *argv[] ) {
    
  //Set local vars
  char *endPtr;
  long intSize;
  char printErr[BUFSIZ];
  char setDownChar;
  char setUpChar;

  //Check valid numbers of command line entered.
  if( isInBounds(argc, MIN_NUM_ARGS, MAX_NUM_ARGS) != 1 ) {
    fprintf( stderr, RADIOACTIVE_PINWHEEL_USAGE, argv[0], MIN_SIZE,
             MAX_SIZE, CHAR_ASCII_MIN, CHAR_ASCII_MAX, DEFAULT_UPWARD_CHAR,
             CHAR_ASCII_MIN, CHAR_ASCII_MAX, DEFAULT_DOWNWARD_CHAR );
    return EXIT_FAILURE;
  }

  //Parse the command line

  //Size
  //set errno to 0 and convert size to int
  errno = 0; 
  intSize = strtol( argv[1], &endPtr, BASE );
  //check converting error
  if( errno ) {
    snprintf( printErr, BUFSIZ, SIZE_CONVERTING_ERR, argv[1], BASE );
    printChar( NEWLINE_CHAR );
    perror( printErr );
    printChar( NEWLINE_CHAR );
   return EXIT_FAILURE;
 }
  //check non-numerical
  if( *endPtr != END_CHAR ){
    fprintf( stderr, SIZE_INT_ERR );
    return EXIT_FAILURE;
  }
  //not in bounds
  if( isInBounds( intSize, MIN_SIZE, MAX_SIZE ) != 1 ){
    fprintf( stderr, SIZE_BOUNDS_ERR, MIN_SIZE, MAX_SIZE );
    return EXIT_FAILURE;
  }
  //check even
  if( isDivisibleBy( intSize, CONSTANT_TWO ) != 1 ){
    fprintf( stderr, SIZE_EVEN_ERR );
    return EXIT_FAILURE;
  }
  
  //check upward_tri and downward_tri
  //if upward_char entered
  if( argc >= 3 ){
    //not a single char
    if( strlen( argv[SEC_INDEX] ) != 1 ){
      fprintf( stderr, SINGLE_CHAR_ERR, UPWARD_CHAR_NAME );
      return EXIT_FAILURE;
    }
    //not in bounds
    if( isInBounds( *argv[SEC_INDEX], CHAR_ASCII_MIN, CHAR_ASCII_MAX ) != 1 ){
      fprintf( stderr, CHAR_BOUNDS_ERR, UPWARD_CHAR_NAME, CHAR_ASCII_MIN,
               CHAR_ASCII_MAX );
      return EXIT_FAILURE;
    }
    
    //set upward char
    setUpChar = *argv[SEC_INDEX];

    //if downward_tri entered, step 3
    if( argc == MAX_NUM_ARGS ){
      //not a single char
      if( strlen( argv[THI_INDEX]) != 1 ){
        fprintf( stderr, SINGLE_CHAR_ERR, DOWNWARD_CHAR_NAME );
        return EXIT_FAILURE;
      }
      //not in bounds
      if( isInBounds( *argv[THI_INDEX], CHAR_ASCII_MIN, CHAR_ASCII_MAX ) != 1 ){
        fprintf( stderr, CHAR_BOUNDS_ERR, DOWNWARD_CHAR_NAME, CHAR_ASCII_MIN,
                 CHAR_ASCII_MAX );
        return EXIT_FAILURE;
      }
      //set downward char
      setDownChar = *argv[THI_INDEX];
    }
    //not dowanward_tri entered, step 4
    else{
      setDownChar = DEFAULT_DOWNWARD_CHAR;
    }

    //check same
    if( setDownChar == setUpChar ){
      fprintf( stderr, UPWARD_DOWNWARD_SAME_CHAR_ERR );
      return EXIT_FAILURE;
    }
  }
  //set default upward_char and downward_char, step 5
  else{
    setDownChar = DEFAULT_DOWNWARD_CHAR;
    setUpChar = DEFAULT_UPWARD_CHAR;
  }
  
  //call function 
  drawRadioactivePinwheel( intSize, setUpChar, setDownChar );

  return EXIT_SUCCESS;

}
