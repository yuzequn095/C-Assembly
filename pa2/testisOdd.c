/*
 * Filename: testisOdd.c
 * Author: Zequn Yu
 * UserId: cs30xga
 * Date: Feb 4th, 2019
 * Sources of Help: None.
 */

#include <stdio.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for isOdd.s
 *
 * int isOdd( int num );
 *
 * Decides if the int passed in is odd or even.
 *
 * Returns 1 if odd.
 * Returns 0 otherwise.
 */
void testisOdd() {

  // Test 0: Odd number.
  TEST( isOdd(41) == 1 );

  // Test 1: 
  TEST( isOdd(1) == 1);

  /*
   * TODO: YOU MUST WRITE MORE TEST CASES FOR FULL POINTS!
   *
   * Some things to think about are error cases, extreme cases, normal cases,
   * abnormal cases, etc.
   */
   TEST( isOdd(4) == 0);
   TEST( isOdd(2) == 0);
   TEST( isOdd(3) == 1);
   TEST( isOdd(5) == 1);
   TEST( isOdd(0) == 0);
   TEST( isOdd(-2) == 0);
   TEST( isOdd(-5) == 1);
   TEST( isOdd(-324) == 0);
   TEST( isOdd(-431) == 1);
   TEST( isOdd(434) == 0);
   TEST( isOdd(777) == 1);
}

int main() {

  fprintf( stderr, "Running tests for isOdd...\n" );
  testisOdd();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
