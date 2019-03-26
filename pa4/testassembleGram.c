/*
 * Filename: testassembleGram.c
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
 * Unit Test for assembleGram.s
 *
 * void assembleGram( gramNode_t * gram, int wordIndex )
 * 
 * Initialize the gram struct
 *
 * Return None, the passed in gram is populated with default values.
 */

void testassembleGram() {
  // TEST CASES
  gramNode_t g;

  int w1 = 3;
  assembleGram( &g, w1 );
  TEST( g.index == 3 );
  TEST( g.count == 0 );
  TEST( g.next == NULL );

  int w2 = 4;
  assembleGram( &g, w2 );
  TEST( g.index == 4 );
  TEST( g.count == 0 );
  TEST( g.next == NULL );

  int w3 = 5;
  assembleGram( &g, w3 );
  TEST( g.index == 5 );
  TEST( g.count == 0 );
  TEST( g.next == NULL );

}

int main() {
  fprintf( stderr, "Running tests for assembleGram...\n" );
  testassembleGram();
  fprintf( stderr, "Done running tests!\n" );

  return 0;

}
