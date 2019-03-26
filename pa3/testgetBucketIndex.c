#include <stdio.h>
#include "pa3.h"
#include "test.h"

void testgetBucketIndex() {

  // test cases 
  //size_t s;

  unsigned int h1 = 5;
  size_t s1 = 2;
  TEST( getBucketIndex( h1, s1 ) == 1 );

  unsigned int h2 = 11;
  size_t s2 = 3;
  TEST( getBucketIndex( h2, s2 ) == 2 );

  unsigned int h3 = 18;
  size_t s3 = 5;
  TEST( getBucketIndex( h3, s3 ) == 3 );

}

int main() {
  fprintf( stderr, "Running tests foor getBucketIndex...\n" );
  testgetBucketIndex();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
