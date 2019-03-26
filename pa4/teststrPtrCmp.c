/*
 * Filename: teststrPtrCmp.c
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
 * Unit Test for strPtrCmp.s
 * 
 * int strPtrCmp( const void * p1, const void * p2 )
 *
 * Compare two pointers to string
 *
 * Return the value of comparing the two strings pointed to with strcmp
 */
void teststrPtrCmp() {
  // TEST CASES
  char * p1 = "apple";
  char * p2 = "banana";
  TEST( strPtrCmp( &p1, &p2 ) <  0 );

  p1 = "abcdef";
  p2 = "ABCDEF";
  TEST( strPtrCmp( &p1, &p2 ) > 0 );

  p1 = "cse30";
  p2 = "cse30";
  TEST( strPtrCmp( &p1, &p2 ) == 0 );
}

int main() {
  fprintf( stderr, "Running tests for strPtrCmp...\n" );
  teststrPtrCmp();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}

