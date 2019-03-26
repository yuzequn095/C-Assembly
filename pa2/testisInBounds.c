/*
 * Filename: testisInBounds.c
 * Author: Zequn Yu
 * UserId: cs30xga
 * Date: Jan 22th, 2019
 * Sources of Help: None
 */ 

#include <stdio.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for isInBounds.s
 *
 * int isInBounds( int value, int minBound, int maxBound );
 *
 * Checks to see if value is within the bounds of minBound (inclusive)
 * to maxBound (inclusive).
 *
 * Returns -1 if minBound > maxBound.
 * Returns 1 if value is between minBound (inclusive) and maxBound (inclusive).
 * Returns 0 otherwise.
 */
void testisInBounds( ) {

  /* Test value in bounds */
  //int res = isInBounds( 1, 0, 2 );
  TEST( isInBounds( 1, 0, 2 ) == 1 );
  
  /* Test value in bounds */
  TEST( isInBounds( 0, 0, 1 ) == 1 );

  /* Test error with bound values */
  TEST( isInBounds( 1, 3, 1 ) == -1 );
  TEST( isInBounds( 1, 5, 3 ) == -1 );
  TEST( isInBounds( 1, 7, 4 ) == -1 );

  /*
   * YOU MUST WRITE MORE TEST CASES FOR FULL POINTS!
   *
   * Some things to think about are error cases, extreme cases, normal cases,
   * abnormal cases, etc.
   */
   TEST( isInBounds( 1, 2, 4 ) == 0 );
   TEST( isInBounds( 1, 1, 4 ) == 1 );
   TEST( isInBounds( 2, 1, 2 ) == 1 );
   TEST( isInBounds( -1, -1, 4 ) == 1 );
   TEST( isInBounds( -2, -1, 5 ) == 0 );
   TEST( isInBounds( -5, -3, -5 ) == -1 );
   TEST( isInBounds( 1, 1, 1 ) == 1 );
}


int main( void ) {

  fprintf( stderr, "Running tests for isInBounds...\n" );
  testisInBounds();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
