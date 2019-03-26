#include <stdio.h>
#include "pa3.h"
#include "test.h"

void testcountChars( ){

  // TEST CASES
  unsigned char c1[26] = { 0 };
  const char * w1 = "HELLO";
  countChars( c1, w1 );
  TEST( c1[7] == 1 );
  TEST( c1[4] == 1 );
  TEST( c1[11] == 2 );
  TEST( c1[14] == 1 );
  TEST( c1[5] == 0 );

  unsigned char c2[26] = { 0 };
  const char * w2 = "HomoMorPhiSM";
  countChars( c2, w2 );
  TEST( c2[7] == 2 );
  TEST( c2[8] == 1 );
  TEST( c2[12] == 3 );
  TEST( c2[18] == 1 );
  TEST( c2[1] == 0 );

  unsigned char c3[26] = { 0 };
  const char *w3 = "";
  countChars( c3, w3 );
  TEST( c3[4] == 0 );
  TEST( c3[9] == 0 );
  TEST( c3[16] == 0 );
}

int main( void ) {
  fprintf( stderr, "Running tests for countChars...\n");
  testcountChars();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
