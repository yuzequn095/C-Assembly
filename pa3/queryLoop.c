/*
 * Filename: queryLoop.c
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Feb 27th,2019
 * Source of Help: None.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "pa3.h"
#include "pa3Strings.h"

#define NEW_LINE '\n'
#define NULL_CHAR '\0'

/*
 * Function Name: queryLoop()
 * void queryLoop( queryTable_t * queryTable );
 * Description: The function handles the interactive mode of the program.
 * Paramaters: queryTable - the table for loop
 * Side Effects: may print new line and prompt to stdout 
 * Error Condition: if no alphabet.
 * Return Value: None.
 */

void queryLoop( queryTable_t * queryTable ) {
  
  // print
  fprintf( stdout, STR_USER_PROMPT );

  // read the word entered by user into buffer
  // replace newline with null char
  char buffer[BUFSIZ];
  while( fgets(buffer, BUFSIZ, stdin) ) {

    // newline
    char *ret = strchr( buffer, NEW_LINE );
    if( ret != NULL ) {
      ret = NULL_CHAR;
    }
    int nonAl = 0;
    // check non-alphabet
    for( int i = 0; i < strlen(buffer) - 1; i++ ) {
      if( isalpha(buffer[i]) == 0 ) {
        fprintf( stderr, STR_NO_ANAGRAMS_FOUND );
        nonAl = 1; 
      }
    }
    // create a new anagram
    if( nonAl == 0 ) {
      anagram_t myAnagram;
      assembleAnagram( buffer, &myAnagram );
      executeQuery( queryTable, &myAnagram );
    }
    // print
    fprintf( stdout, STR_USER_PROMPT );
  } 
  
  //print
  fprintf( stdout, STR_NEWLINE_CHAR );
}
