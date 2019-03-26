#include <stdio.h>
#include "pa2.h"
#include "test.h"

void testprocessPassphrase( ){
  char s1[] = { 'A', 'p', 'p', 'L', '3', '0', 's', 's', '\0' };
  unsigned char p1[8];
  int v1 = processPassphrase( s1, p1 );
  for( int i = 0; i < sizeof(p1); i++ ){
    printf( "%c\n", p1[i] );
  }
  TEST( v1 == 0 );

  char s2[] = { 'i', 'P', 'h', '0', 'n', '3', '\0' };
  unsigned char p2[8];
  int v2 = processPassphrase( s2, p2 );
  for( int i = 0; i < sizeof(p2); i++ ) {
    printf( "%c\n", p2[i] );
  }
  TEST( v2 == 0 );

  char s3[1] = { 'M' };
  unsigned char p3[8];
  int v3 = processPassphrase( s3, p3 );
  TEST( v3 == -4 );

  char s4[9] = { 'a', 'b', 'c', 'd', 'e', 'f', 'h', 'i', 'j' };
  unsigned char p4[8];
  int v4 = processPassphrase (s4, p4 );
  TEST( v4 == -4 );
}
int main( void ) {
  fprintf( stderr, "Running tests for processPassphrase...\n" );
  testprocessPassphrase();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
