/*
 * Filename: loadVocabulary.c
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Mar 5th, 2019
 * Source of Help: Di slides.
 */

#include <stdio.h>
#include <stdlib.h>
#include "pa4.h"
#include "pa4Strings.h"
#include <string.h>
#include <errno.h>

#define NEW_LINE '\n'
#define NULL_TERM '\0'

/*
 * Function Name: loadVocabulary()
 * Function Prototype: int loadVocabulary( vocab_t * vocab, FILE * vocabFile )
 * Description: This function is used to load the words from the vocabulary 
 *              file into struct.
 * Side Effects: Print error output to stderr.
 * Error Conditions: Error allocating dynamic memory
 * Return Value: 0 if successful, -1 if error.
 */

int loadVocabulary( vocab_t * vocab, FILE * vocabFile ) {
   
  // set var
  char **tmpPtr = NULL;
  
  // Check argument
  if( vocab == NULL ) {
    return 0;
  }
  if ( vocabFile == NULL ) {
    return 0;
  }

  // use fgets to read words one at a time, reading into a char buffer
  char buffer[BUFSIZ];
  errno = 0;
  char *nl;
  int len;
  
  // initialize
  vocab->words = NULL;
  vocab->numWords = 0;

  // read
  while( fgets( buffer, BUFSIZ, vocabFile) != NULL ) {
    // check if too long
    int tooLong = 1;

    // null each word
    nl = strchr( buffer, NEW_LINE );
    // check new line
    if( nl != NULL ) {
      *nl = NULL_TERM;
      tooLong = 0;
    }
  
    // Allocate space for each word (calloc)
    if( tooLong == 0 ) {
      len = strlen(buffer) + 1;
    }
    else{
      // set last cell to null
      buffer[BUFSIZ-1] = NULL_TERM;
      len = strlen(buffer) + 1;
    }
    char *myWord = calloc(len, sizeof(char));
    // check fail
    if( myWord == NULL ) {
      fprintf( stderr, STR_ERR_MEM );
      // free memory
      for( int i = 0; i < vocab->numWords; i++ ) {
        free( vocab->words[i] );
      }
      free( vocab->words );
      return -1;
    }
    // copy
    strncpy( myWord, buffer, len );

    // resize vocab's words
    int newSize = (vocab->numWords)*sizeof(vocab->words) 
                  + sizeof(vocab->words);
    tmpPtr = realloc( vocab->words, newSize );
    // check fail
    if( tmpPtr == NULL ) {
      fprintf( stderr, STR_ERR_MEM );
      // free
      for( int i = 0; i < vocab->numWords; i++ ) {
        free( vocab->words[i] );
      }
      free( vocab->words );
      return -1;
    }
    
    // assign
    vocab->words = tmpPtr;
    (vocab->words)[vocab->numWords] = myWord;
    (vocab->numWords)++;
  }

  return 0;
}
