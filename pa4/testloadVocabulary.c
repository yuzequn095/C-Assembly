/*
 * Filename: testloadVocabulary.c
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Mar 5th, 2019
 * Source of Help: None.
 */

#include "pa4.h"
#include "test.h"
#include <stdio.h>
#include <string.h>

/*
 * Unit Test for loadVocabulary.c
 * 
 * int loadVocabulary ( vocab_t * vocab, FILE * vocabFile )
 *
 * Load words read from file to vocab.
 *
 * Return 0 if successful, -1 if error.
 */
 void testloadVocabulary() {
   // TEST CASES
   char *words[] = {"a", "b", "c", "d", "e", "f"};
   size_t numWords = sizeof(words) / sizeof(*words);
   vocab_t v = { words, numWords };
   FILE * file = fopen( "myWord.vocab", "r" );
   loadVocabulary( &v, file );
   TEST( strcmp( v.words[0], "g" ) == 0 );
   TEST( strcmp( v.words[1], "h" ) == 0 );
   TEST( strcmp( v.words[2], "i" ) == 0 );
   TEST( v.numWords == 3 );

   vocab_t vocab;
   file = fopen( "myWord.vocab", "r" );
   loadVocabulary( &vocab, file );
   TEST( strcmp( vocab.words[0], "g" ) == 0 );
   TEST( strcmp( vocab.words[1], "h" ) == 0 );
   TEST( strcmp( vocab.words[2], "i" ) == 0 );
   TEST( vocab.numWords == 3 );
 
   FILE *f1 = fopen( "non", "r" );
   TEST( loadVocabulary( &vocab, f1 ) == 0 );

   vocab_t v1;
   v1.words = NULL;
   v1.numWords = 0;
   file = fopen( "myWord.vocab", "r" );
   loadVocabulary( &v1, file );
   TEST( strcmp( vocab.words[0], "g" ) == 0 );
   TEST( loadVocabulary( &v1, file ) == 0 );
   
   file = fopen( "myWord.vocab", "r" );
   loadVocabulary(NULL, file);
   TEST( loadVocabulary( &v1, file ) == 0 );
 }

 int main() {
   
   fprintf( stderr, "Running tests for loadVocabulary...\n" );
   testloadVocabulary();
   fprintf( stderr, "Done running tests!\n" );

   return 0;
 }
