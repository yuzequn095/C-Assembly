/*
 * Filename: testgetRemainder.c
 * Author: Zequn Yu
 * UserId: cs30xga
 * Date: Jan 22th, 2019
 * Source of Help: None
 */

#include <stdio.h>
#include "pa1.h"
#include "test.h"

/*
 * Unit Test for getRemainder.s
 *
 * int getRemainder( int dividend, int divisor );
 *
 * Checks to see if value is equal to the correct remainder.
 *
 * Return the same remainder is correct.
 */
void testgetRemainder( ) {
  
  /* Test Cases */
  TEST( getRemainder( 5, 2 ) == 1 );
  TEST( getRemainder( 11, 3 ) == 2 );
  TEST( getRemainder( 0, 7 ) == 0 );
  TEST( getRemainder( -5, -2 ) == -1 );
  TEST( getRemainder( -15, 6 ) == -3 );
  TEST( getRemainder( 18, -5 ) == 3 );
}

 int main( void ) {
   
   fprintf(stderr, "Running tests for getRemainder...\n");
   testgetRemainder();
   fprintf(stderr, "Done running tests!\n");

   return 0;
}
