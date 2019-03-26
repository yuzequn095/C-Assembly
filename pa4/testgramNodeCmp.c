/*
 * Filename: testgramNodeCmp.c
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
 * Unit Test for gramNodeCmp.s
 *
 * int gramNodeCmp( const void *p1, const void *p2 )
 * 
 * Compare the index of two pointers to struct
 *
 * Return -1 if smaller, 0 if equal, 1 if bigger
 */

void testgramNodeCmp() {
  // TEST CASES
  gramNode_t g1;
  gramNode_t g2;
  g1.index = 2;
  g2.index = 3;
  TEST( gramNodeCmp( &g1, &g2 ) == -1 );

  g1.index = 3;
  g2.index = 3;
  TEST( gramNodeCmp( &g1, &g2 ) == 0 );

  g1.index = 3;
  g2.index = 2;
  TEST( gramNodeCmp( &g1, &g2 ) == 1 );
}

int main() {
  fprintf( stderr, "Running tests for gramNodeCmp...\n");
  testgramNodeCmp();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
