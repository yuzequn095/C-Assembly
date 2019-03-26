/*
 * Filename: testgenerateMask.c
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Feb 5th, 2019
 * Source of Help: None
 */

 #include <stdio.h>
 #include "pa2.h"
 #include "test.h"

 /*
  * Unit Test for generateMask
  *
  * void generateMask( unsigned char keys[], unsigned char passphrase[],
  *                      unsigned char mask[] );
  *
  * Check to see if mask is correct
  *
  */

  void testgenerateMask( ) {
    
    /* Test Cases */
    unsigned char k1[] = { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x11, 0x22 };
    unsigned char p1[] = { 0x22, 0x11, 0xFF, 0xEE, 0xDD, 0xCC, 0xBB, 0xAA };
    unsigned char m1[8];
    generateMask( k1, p1, m1 );
    TEST( m1[0] == 0x88 );
    TEST( m1[1] == 0xAA );
    TEST( m1[2] == 0x33 );
    TEST( m1[4] == 0x33 );
   

    unsigned char k2[] = { 0xCC, 0xBB, 0x98, 0xFF, 0xEE, 0xFF, 0x16, 0x22 };
    unsigned char p2[] = { 0x22, 0xAA, 0xFF, 0xEE, 0x13, 0xAC, 0xBB, 0xBA };
    unsigned char m2[8];
    generateMask( k2, p2, m2 );
    TEST( m2[0] == 0xEE );
    TEST( m2[2] == 0x67 );
    TEST( m2[4] == 0xFD );
    TEST( m2[6] == 0xAD );
  
  }

  int main( void ) {

    fprintf( stderr, "Running tests for generateMask...\n" );
    testgenerateMask();
    fprintf( stderr, "Done running tests!\n" );

    return 0;

  }
