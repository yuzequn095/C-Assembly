/* 
 * Filename: main.c
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Feb 13th, 2019
 * Source of Help: Di.
 */

#include <stdio.h>
#include <stdlib.h>
#include "pa2.h"
#include "pa2Strings.h"
#include "errno.h"
#include <string.h>

#define HALF_KEY 4
#define NEW_LINE "\n"


/* 
 * Function Name: main()
 * Function prototype: int main( int argc, char *argv[] );
 * Description: Drive the rest of the program. It will also check errors.
 * Parameters: argc - number of command line passed in.
 *             argv - command line arguments passed in.
 * Side Effects: Pritins information to stdout or stderr.
 * Error Condition: Wrong number of parameters or error condition in function.
 * Return Value: EXIT_SUCCESS if no errors, otherwise EXIT_FAILURE.
 */
int main( int argc, char *argv[] ) {
  //set local var
  int errNum = 0;
  char printErr[BUFSIZ];

  // Drive the rest of the program
  // disable buffering on stdout
  (void) setvbuf( stdout, NULL, _IONBF, 0 );

  // check number
  if( argc != EXPECTED_ARGS + 1 ) {
    fprintf( stderr, STR_USAGE, argv[0], MIN_PASSPHRASE_SIZE, 
             MAX_PASSPHRASE_SIZE, MIN_ROTATE, MAX_ROTATE );
    return EXIT_FAILURE;
  }

  // print error and exit if error encounters
  // passphrase
  unsigned char passArray[MAX_PASSPHRASE_SIZE] = { INIT_PASSPHRASE,
                                                   INIT_PASSPHRASE, 
                                                   INIT_PASSPHRASE, 
                                                   INIT_PASSPHRASE,
                                                   INIT_PASSPHRASE, 
                                                   INIT_PASSPHRASE, 
                                                   INIT_PASSPHRASE, 
                                                   INIT_PASSPHRASE};
  // call function 
  errNum = processPassphrase( argv[1], passArray );
  // check errors
  if( errNum == LENGTH_ERR ) {
    fprintf( stderr, STR_ERR_BAD_PASSPHRASE, MIN_PASSPHRASE_SIZE,
             MAX_PASSPHRASE_SIZE );
    return EXIT_FAILURE;
  }


  // keys( key0 and key1 )
  unsigned char keyArray[KEY_SIZE];
  // key0 first
  unsigned char oneArray[HALF_KEY];
  errNum = processKey( argv[2], oneArray );
  // check key0 errors
  if ( errNum == ERANGE_ERR ) {
    snprintf( printErr, BUFSIZ, STR_ERR_CONVERTING, argv[2], DEF_BASE );
    perror( printErr );
    fprintf( stdout, NEW_LINE );
    return EXIT_FAILURE;
  } 
  if( errNum == ENDPTR_ERR ) {
    fprintf( stderr, STR_ERR_NOTINT, argv[2] );
    return EXIT_FAILURE;
  }
  // key1 second
  unsigned char twoArray[HALF_KEY];
  errNum = processKey( argv[3], twoArray );
  // check key1 errors
  if( errNum == ERANGE_ERR ) {
    snprintf( printErr, BUFSIZ, STR_ERR_CONVERTING, argv[3], DEF_BASE );
    perror( printErr );
    fprintf( stdout, NEW_LINE );
    return EXIT_FAILURE;
  }
  if( errNum == ENDPTR_ERR ) {
    fprintf( stderr, STR_ERR_NOTINT, argv[3] );
    return EXIT_FAILURE;
  }
  // no errors then combine
  for( int i = 0; i < HALF_KEY; i++ ) {
    keyArray[i] = oneArray[i];   
  }
  for( int j = HALF_KEY; j < KEY_SIZE; j++ ) {
    keyArray[j] = twoArray[j - HALF_KEY];
  }

  // rotateValue
  int rotValue = 0;
  errNum = processRotateValue( argv[4], &rotValue );
  if( errNum == ERANGE_ERR ) {
    snprintf( printErr, BUFSIZ, STR_ERR_CONVERTING, argv[4], DEF_BASE );
    perror( printErr );
    fprintf( stdout, NEW_LINE );
    return EXIT_FAILURE;
  }
  if( errNum == ENDPTR_ERR ) {
    fprintf( stderr, STR_ERR_NOTINT, argv[4] );
    return EXIT_FAILURE;
  }
  if( errNum == BOUND_ERR ) {
    fprintf( stderr, STR_ERR_BAD_ROT, MIN_ROTATE, MAX_ROTATE );
    return EXIT_FAILURE;
  }

  // if no error occurred
  // create mask
  unsigned char mask[MASK_SIZE];
  generateMask( keyArray, passArray, mask );

  // encrypt
  FILE * infile = stdin;
  cipher( infile, mask, rotValue );

  return EXIT_SUCCESS;
}  
