/*
 * Filename: testwordToIndex.c
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Mar 5th , 2019
 * Source of Help: None.
 */

#include "pa4.h"
#include "test.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * Unit Test for wordToIndex.c
 *
 * int wordToIndex( const char * word, vocab_t * vocab )
 *
 * Check if the index returned was correct.
 */

 void testwordToIndex() {
   // Test cases
   char *words[] = {"a", "b", "c", "d", "e", "f"};
   size_t numWords = sizeof(words) / sizeof(*words);
   vocab_t v1 = { words, numWords };

   const char * w1 = "b";
   TEST( wordToIndex( w1, &v1 ) == 1 );

   const char * w2 = "a";
   TEST( wordToIndex( w2, &v1 ) == 0 );

   const char * w3 = "d";
   TEST( wordToIndex( w3, &v1 ) == 3 );
 }

 int main() {
   fprintf ( stderr, "Running tests for wordToIndex...\n" );
   testwordToIndex();
   fprintf( stderr, "Done running tests!\n" );

   return 0;
 }
