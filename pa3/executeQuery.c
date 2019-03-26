/*
 * Filename: executeQuery.c
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Feb 27th, 2019
 * Source of Help: None.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "pa3.h"
#include "pa3Strings.h"
#include <strings.h>

/*
 * Function Name: executeQuery()
 * Function Prototype: void executeQuery( queryTable_t * queryTable,
 *                     anagram_t * needle );
 * 
 * Description: This function handles the actual query for the anagrams.
 * Side Effects: May output to stderr.
 * Error Conditions: None.
 * Return Value: None.
 */
 

void executeQuery( queryTable_t *queryTable, anagram_t *needle ) {

  // calculate the index into queryTable that needle would be found 
  int idx = getBucketIndex( needle -> hashcode, queryTable -> size );
  anagram_t *dataPtr = queryTable->tablePtr[idx].dataPtr;
  
  
  // search for anagrams in stored array of anagrams in bucket at idx
  // use bsearch 
  anagram_t *searchItem;
  searchItem = bsearch( needle, dataPtr,
                        queryTable->tablePtr[idx].anagramCount, 
                        sizeof(anagram_t), anagramCmp );
  // if return null pointer, then no anagrams found, print error
  if( searchItem == NULL ) {
    fprintf( stdout, STR_NO_ANAGRAMS_FOUND );
    return;
  }
  
  // if found, to find the first match anagram_t.
  // step backward (determine if counts = 0 )
  int backWard = 0;
  while( backWard == 0 ) {
    searchItem = searchItem - 1;
    // if not same or at the beginning leave loop
    if( anagramCmp( searchItem, needle ) != 0 && searchItem == NULL ) {
      backWard = 1;
    }
    // if same, then continue go next loop
    if( anagramCmp( searchItem, needle ) == 0 && searchItem != NULL) {
      continue;
    }
  }// backward loop ends

  // traverse forward through the array of anagram_t and print out anagram
  // dont't print same words
  // hint: strncat
  int forWard = 0;
  char *anaString = NULL;
  memset( anaString, 0, queryTable->size); 
  while( forWard==0 ) {
    searchItem = searchItem + 1;
    // if same or end
    if( anagramCmp( searchItem, needle ) != 0 && searchItem == NULL ) {
      forWard = 1;
    }
    // if not same, continue
    if( anagramCmp( searchItem, needle ) == 0 && searchItem != NULL){ //&& 
       if (strncasecmp( searchItem->originalWord, needle->originalWord,
           MAX_WORD_SIZE) != 0 ){
         // build string
        strncat( anaString, dataPtr->originalWord, MAX_WORD_SIZE );
        strncat( anaString, STR_SPACE_CHAR, 1 );
        continue;
      }
    }
  }// forward loop ends
  
  // print out
  fprintf( stdout, STR_ANAGRAMS_FOUND );
  fprintf( stdout, anaString );
  fprintf( stdout, STR_NEWLINE_CHAR );
}
