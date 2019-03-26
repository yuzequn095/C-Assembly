/*
 * Filename: testrotate.c
 * Author: Zequn Yu
 * UserId: cs30xga
 * Date: Feb 6th, 2019
 * Source of Help: None
 */

 #include <stdio.h>

 #include "pa2.h"
 #include "test.h"

/*
 * Unit Test for rotate.s
 *
 * void rotate( unsigned char mask[], int rotateValue );
 *
 * Check if the mask[] is correct after rotated.
 *
 */

 void testrotate( ) {
   
   /* TEST CASES */
   unsigned char mask[8] = { 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00 };
   int v = 3;
   rotate( mask, v );
   TEST( mask[0] == 0x00 );
   TEST( mask[1] == 0x07 );
   TEST( mask[2] == 0xF8 );
   TEST( mask[3] == 0x00 );
   TEST( mask[4] == 0x07 );
   TEST( mask[5] == 0xF8 );
   TEST( mask[6] == 0x00 );
   TEST( mask[7] == 0x00 );
 
 
   unsigned char m1[8] = { 0xAA, 0XFA, 0X34, 0x78, 0xBC, 0xCD, 0x23, 0x88 };
   int v1 = 8;
   rotate( m1, v1 );
   TEST( m1[0] == 0x88 );
   TEST( m1[1] == 0xAA );
   TEST( m1[2] == 0xFA );
   TEST( m1[3] == 0x34 );
   TEST( m1[4] == 0x78 );
   TEST( m1[5] == 0xBC );
   TEST( m1[6] == 0xCD );
   TEST( m1[7] == 0x23 );
 
   unsigned char test5[] = { 0xAB, 0xBC, 0xCD, 0xDE, 0xEF, 0x01, 0x12, 0x23 };
   rotate( test5, 128 );
   TEST( test5[0] == 0xAB );
   TEST( test5[1] == 0xBC );
   TEST( test5[2] == 0xCD );
 
   rotate( test5, 64 );
   TEST( test5[0] == 0xAB );
   TEST( test5[1] == 0xBC );
   TEST( test5[2] == 0xCD );

   //unsigned char test8[] = { 0x89, 0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67 };
   //rotate( test8, 82 );
   //TEST( test8[0] == 0xD1 );
   //TEST( test8[1] == 0x59 );
   //TEST( test8[2] == 0xE2 );
 }

 int main( void ) {

   fprintf( stderr, "Running tests for rotate...\n" );
   testrotate();
   fprintf( stderr, "Done running tests!\n" );

   return 0;
 }
