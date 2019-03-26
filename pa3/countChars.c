/*
 * Filename: countChars.s
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Feb 27th, 2019
 * Source of Help: https://www.geeksforgeeks.org/tolower-function-in-c/
 */


#include <stdio.h>
#include <stdlib.h>
#include "pa3.h"
#include "pa3Strings.h"
#include <string.h>
#include <ctype.h>

#define DEFAULT_IDX 97
#define NULL_CHAR '\0'

/*
 * Function Name: countChars()
 * Function prototype: void countChars( unsigned char counts[], 
 *                                      const char * word )
 * Description: This function will count the occurrences of 
 *              each character in the passed in word and store
 * Parameter: counts[] - the array for store
 *            word - the string passed in
 * Side Effects: None.
 * Error Condition: word is null 
 * Return Value: None.
 */

void countChars( unsigned char counts[], const char * word ) {
  

  //init
  for( int i = 0; i < ALPHABET_SIZE; i++ ) {
    counts[i] = 0;
  }

  // check if word is null
  if( word == NULL_CHAR ) {
    return;
  }


  // convert all chars in word to lowercase
  int i = 0;
  char ch;
  int ascii;

  while( word[i] ) {
    ch = word[i];
    // call tolower to convert
    ch = tolower(ch);
    
    // count occurences
    ascii = (int)ch - DEFAULT_IDX;
    counts[ascii] = counts[ascii] + 1;
    i++;
  }
  
}
