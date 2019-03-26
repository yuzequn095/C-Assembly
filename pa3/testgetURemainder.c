#include <stdio.h>
#include "pa3.h"
#include "test.h"

void testgetURemainder() {

  // Test cases
  TEST( getURemainder( 5, 2 ) == 1 );
  TEST( getURemainder( 11, 3 ) == 2 );
  TEST( getURemainder( 18, 5 ) == 3 );
}

int main() {
  fprintf( stderr, "Running tests for getURemainder...\n");
  testgetURemainder();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
