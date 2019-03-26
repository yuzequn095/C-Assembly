#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "test.h"
#include "pa3.h"

unsigned int hash( unsigned char counts[] ) {
  unsigned int hash = HASH_START_VAL;
  for ( int i = 0; i < ALPHABET_SIZE; i++ ) {
    hash = hash * HASH_PRIME + counts[i];
  }
  return hash;
}

void testgetHashcode() {
  // TEST CASE
  unsigned char c1[26] = { 0 };
  c1[5] = 1;
  c1[7] = 3;
  c1[17] = 2;
  c1[22] = 4;
  TEST( hash( c1 ) == getHashcode( c1 ) );

  unsigned char c2[26] = { 0 };
  c2[3] = 1;
  c2[7] = 3;
  c2[14] = 7;
  c2[20] = 5;
  TEST( hash( c2) == getHashcode( c2 ) );
}

int main( void ) {
  
  fprintf( stderr, "Running tests for getHashcode...\n" );
  testgetHashcode();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
