#include "pa3.h"
#include "test.h"
#include <stdio.h>

void testcountsCmp() {

  // instance
  anagram_t a1;
  anagram_t a2;

  for( int i = 0 ; i < ALPHABET_SIZE ; i++ ){
    a1.counts[i] = (unsigned char)0;
    a2.counts[i] = (unsigned char)0;
  }
  int v1 = countsCmp( &a1, &a2 );
  TEST( v1 == 0 );

  a1.counts[4] = 5;
  a2.counts[4] = 3;
  TEST( countsCmp( &a1, &a2 ) == 1 );

  a1.counts[4] = 0;
  a2.counts[4] = 7;
  TEST( countsCmp( &a1, &a2 ) == -1 );
}

int main() {
  fprintf( stderr, "Running tests for countsCmp...\n");
  testcountsCmp();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
