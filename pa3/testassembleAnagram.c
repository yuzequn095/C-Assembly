#include "pa3.h"
#include "test.h"
#include <stdio.h>
#include <string.h>

#define MAX 26

void testassembleAnagram() {
  const char *o1 = "Hello";
  anagram_t a1;
  unsigned char c1[26] = { 0 };
  int h1;
  countChars( c1, o1 );
  h1 = getHashcode( c1 );
  for( int i = 0; i < MAX; i++ ) {
    a1.counts[i] = 0;
  }
  assembleAnagram( o1, &a1 );
  TEST( strncmp( a1.originalWord, o1, strlen( o1 ) ) == 0 );
  TEST( a1.counts[7] == 1 );
  TEST( a1.counts[4] == 1 );
  TEST( a1.counts[11] == 2 );
  TEST( a1.counts[14] == 1 );
  TEST( a1.counts[5] == 0 );
  TEST( a1.hashcode == h1 );
}

int main() {
  fprintf( stderr, "Running tests for assembleAnagram...\n" );
  testassembleAnagram();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}

