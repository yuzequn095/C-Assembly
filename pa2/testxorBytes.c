/*
 * Filename: testxorBytes.c
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Feb 5th, 2019
 * Source of Help: None
 */

 #include <stdio.h>
 #include "pa2.h"
 #include "test.h"

 /*
  * Unit Test for xorBytes
  * 
  * void xorBytes( unsigned char originalText[], unsigned char mask[],
  *                 unsigned char cipherText[], unsigned int numBytes );
  *
  * Check to see if cipherText is correct 
  *
  */

 void testxorBytes( ) {
  
  /* Test cases */
  unsigned char ori[1] = { '0' };
  unsigned char mask[1] = { '0' };
  unsigned char cipher[1];
  unsigned int num = 1;
  xorBytes( ori, mask, cipher, num );
  TEST( cipher[0] == 0x00 );
  
  unsigned char ori2[2] = { 0xFF, 0x61 };
  unsigned char mask2[2] = { 0x61, 0x6D };
  unsigned char cipher2[2];
  unsigned int num2 = 2;
  xorBytes( ori2, mask2, cipher2, num2 );
  TEST( cipher2[0] == 0x9E );
  TEST( cipher2[1] == 0x0C );
  
  unsigned char ori3[2] = { 0x62, 0x8A };
  unsigned char mask3[2] = { 0x61, 0x77 };
  unsigned char cipher3[2];
  unsigned int num3 = 2;
  xorBytes( ori3, mask3, cipher3, num3 );
  TEST( cipher3[0] == 0x03 );
  TEST( cipher3[1] == 0xFD );
 
  unsigned char ori4[2] = { 0x62, 0x8A };
  unsigned char mask4[2] = { 0x61, 0x77 };
  unsigned char cipher4[2] = { 0xFF, 0XFF };
  unsigned int num4 = 1;
  xorBytes( ori4, mask4, cipher4, num4 );
  TEST( cipher4[0] == 0x03 );
  TEST( cipher4[1] == 0xFF );

  unsigned char ori5[2] = { 0x62, 0x8A };
  unsigned char mask5[2] = { 0x61, 0x77 };
  unsigned char cipher5[2] = { 0xFF, 0XFF };
  unsigned int num5 = 0;
  xorBytes( ori5, mask5, cipher5, num5 );
  TEST( cipher5[0] == 0xFF );
  TEST( cipher5[1] == 0xFF );
 
 }



 int main( void ) {

   fprintf( stderr, "Running tests for xorBytes...\n" );
   testxorBytes();
   fprintf( stderr, "Done running tests!\n" );

   return 0;

 }
   
