#include "pa3.h"
#include "test.h"
#include <stdio.h>

void testhashcodeCmp() {
  
  // create instance
  anagram_t a1;
  anagram_t a2;

  a1.hashcode = 12;
  a2.hashcode = 12;
  int v1 = hashcodeCmp( &a1, &a2 );
  TEST( v1 == 0 );
  //TEST( hashcodeCmp( &a1.hashcode, &a2.hashcode ) == 0 );

  a1.hashcode = 11;
  a2.hashcode = 13;
  TEST( hashcodeCmp( &a1, &a2 ) == -1 );

  a1.hashcode = 13;
  a2.hashcode = 11;
  TEST( hashcodeCmp( &a1, &a2 ) == 1 );
}

int main() {
  fprintf( stderr, "Running tests for hashcodeCmp...\n" );
  testhashcodeCmp();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
