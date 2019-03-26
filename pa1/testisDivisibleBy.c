/* 
 * Filename: testisDivisibleBy.c
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Jan 22th, 2019
 * Source of Help: None
 */

#include <stdio.h>

#include "pa1.h"
#include "test.h"

/*
 * Unit Test for isDivisibleBy.s
 * 
 * int isDivisibleBy( int num, int divisor );
 * 
 * Checks to see if num can be evenly divisible by divisor.
 *
 * Returns -1 if an error occurred.
 * Returns 1 if num is evenly divisible by divisor.
 * Returns 0 if not.
 */
 void testisDivisibleBy( ) {
   
   /* Test Cases */
   TEST( isDivisibleBy( 3, 3 ) == 1 );
   TEST( isDivisibleBy( 6, 2 ) == 1 );
   TEST( isDivisibleBy( 7, 1 ) == 1 );
   TEST( isDivisibleBy( 6, 4 ) == 0 );
   TEST( isDivisibleBy( 13, 2 ) == 0 );
   TEST( isDivisibleBy( 1, 0 ) == -1 );
   TEST( isDivisibleBy( 1, -3 ) == -1 );

}

int main( void ) {
  
  fprintf( stderr, "Running tests for isDivisibleBy...\n" );
  testisDivisibleBy();
  fprintf( stderr, "Done running tests!\n" );
 
  return 0;
}
