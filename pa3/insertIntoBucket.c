/* 
 * Function Name: insertIntoBucket.c
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Feb 27th, 2019
 * Source of Help: None.
 */

#include <stdio.h>
#include <stdlib.h>
#include "pa3.h"
#include "pa3Strings.h"
#include <string.h>

/* 
 * Function Name: insertIntoBucket
 * Function Prototype: int insertIntoBucket( bucket_t * bucket, 
 *                                     anagram_t * anagram ) 
 * Description: This function will insert anagram to bucket, appending it 
 *              to the end of the array of anagrams in bucket.
 * Parameters: bucket - the bucket to be inserted
 *             anagram - the data from
 * Side Effects: It may output error information to stderr.
 * Error Conditions: realloc fails.
 * Return value: -1 if any error occurred, 0 otherwise
 */

int insertIntoBucket( bucket_t * bucket, anagram_t * anagram ) {

  // use realloc to increase the size of the bucket's anagram array
  // error checking ( free dataPtr in bucket )
  // use a tmp ptr to store the return ptr of realloc()
  // successful - assign dataPtr to newly allocated memory (put in new ana)
  anagram_t *tmpPtr;
  // use malloc for dataPtr
  //bucket -> dataPtr = malloc(1);
  // get the new size with a new anagram which will be added
  int newSize = sizeof(bucket -> anagramCount) * sizeof(anagram_t) 
                + sizeof(anagram_t);
  tmpPtr = realloc( bucket -> dataPtr, newSize );
  // realloc failure
  if( tmpPtr == NULL ) {
    fprintf( stderr, STR_ERR_MEM );
    free( bucket -> dataPtr );
    return -1;
  }
  
  // reassign
  bucket -> dataPtr = tmpPtr;
  (bucket -> dataPtr)[bucket -> anagramCount] = *anagram; 
  (bucket -> anagramCount)++;
  return 0;
}
