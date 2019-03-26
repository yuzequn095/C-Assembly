/*
 * Filename: testanagramCmp.c
 * Author: Zequn Yu
 * UserId: cs30xga
 * Date: Feb 19th, 2019
 * Sources of Help: Di slides
 */

#include "pa3.h"
#include "test.h"
#include <stdio.h>

/*
 * Unit Test for anagramCmp.s
 *
 * int anagramCmp( const void * p1, const void * p2 );
 *
 * Compares two anagrams, first by hashcode, then by counts (as a tie-breaker).
 *
 * Returns -1 if anagram p1 has a smaller hashcode than anagram p2
 *         -1 if anagram p1 has the same hashcode but smaller countsCmp result
 *                than anagram p2
 *         +1 if anagram p1 has a larger hashcode than anagram p2
 *         +1 if anagram p1 has the same hashcode but larger countsCmp result
 *                than anagram p2
 *          0 if anagram p1 has the same hashcode and counts as anagram p2
 */
void testanagramCmp() {

  // Create two anagrams to test with
  anagram_t anagram1;
  anagram_t anagram2;

  // Start with all the letter counts at zero
  for( int i = 0 ; i < ALPHABET_SIZE ; i++ ){
    anagram1.counts[i] = (unsigned char)0;
    anagram2.counts[i] = (unsigned char)0;
  }


  // Test when two anagrams are the same
  anagram1.hashcode = 12;
  anagram2.hashcode = 12;
  anagram1.counts[12] = (unsigned char)12;
  anagram2.counts[12] = (unsigned char)12;

  TEST( anagramCmp( &anagram1, &anagram2 ) == 0 );

  /*
   * TODO: YOU MUST WRITE MORE TEST CASES FOR FULL POINTS!
   *
   * Some things to think about are all the different possible return values,
   * normal cases, abnormal cases, extreme cases, etc.
   */
  
  anagram_t a1;
  anagram_t a2;
  for( int i = 0 ; i < ALPHABET_SIZE ; i++ ){
    a1.counts[i] = (unsigned char)0;
    a2.counts[i] = (unsigned char)0;
  }
  a1.hashcode = 11;
  a2.hashcode = 12;
  a1.counts[1] = (unsigned char)3;
  a2.counts[1] = (unsigned char)2;
  int v1 = anagramCmp( &a1, &a2 );
  TEST( v1 == -1 );
  //TEST( anagramCmp( &a1, &a2 ) == -1 );

  a1.hashcode = 12;
  a2.hashcode = 12;
  a1.counts[1] = (unsigned char)1;
  a2.counts[1] = (unsigned char)2;
  TEST( anagramCmp( &a1, &a2 ) == -1 );

  a1.hashcode = 13;
  a2.hashcode = 11;
  a1.counts[1] = (unsigned char)1;
  a2.counts[1] = (unsigned char)5;
  TEST( anagramCmp( &a1, &a2 ) == 1 );

  a1.hashcode = 10;
  a2.hashcode = 10;
  a1.counts[1] = (unsigned char)5;
  a2.counts[1] = (unsigned char)2;
  TEST( anagramCmp( &a1, &a2 ) == 1 );

}

int main() {
  fprintf( stderr, "Running tests for anagramCmp...\n" );
  testanagramCmp();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
} 
