/*
 * Filename: testprocessKey.c
 * Author: Zequn Yu
 * UserId: cs30xga
 * Date: Feb 4th, 2019
 * Source of Help: None
 */

 #include <stdio.h>
 #include "pa2.h"
 #include "test.h"

/*
 * Unit Test for processKey
 *
 * int processKey( char * str, unsigned char key[] );
 *
 * Checks to see if return value is correct and if key[] contains correct value
 *
 * Return 0 means converting sucessful.
 * Return ERANGE_ERR or ENDPTR_ERR otherwise, based on error type.
 */

 void testprocessKey( ) {
 
   /* TEST CASES */
   char *str1 = "0xAB";
   unsigned char key1[4];
   TEST( processKey( str1, key1 ) == 0 );
   TEST( key1[0] == 0x00 );
   TEST( key1[1] == 0x00 );
   TEST( key1[2] == 0x00 );
   TEST( key1[3] == 0xAB );

   char *str2 = "0xABCD";
   unsigned char key2[4];
   TEST( processKey( str2, key2 ) == 0 );
   TEST( key2[0] == 0x00 );
   TEST( key2[1] == 0x00 );
   TEST( key2[2] == 0xAB );
   TEST( key2[3] == 0xCD );


   char *str3 = "0xABCDEF";
   unsigned char key3[4];
   TEST( processKey( str3, key3 ) == 0 );
   TEST( key3[0] == 0x00 );
   TEST( key3[1] == 0xAB );
   TEST( key3[2] == 0xCD );
   TEST( key3[3] == 0xEF );
 
   char *str4 = "123happynewyear";
   unsigned char key4[4];
   TEST( processKey( str4, key4 ) == 0 );
   TEST( key4[0] == 0x00 );
   TEST( key4[1] == 0x00 );
   TEST( key4[2] == 0x00 );
   TEST( key4[3] == 0x7B );
 
   char *str5 = "9999999999999999999999";
   unsigned char key5[4];
   TEST( processKey( str5, key5 ) == -2);

   char *str6 = "tobeornottobe";
   unsigned char key6[4];
   TEST( processKey( str6, key6 ) == -1);
 }

 int main( void ) {

   fprintf( stderr, "Running tests for processKey...\n" );
   testprocessKey();
   fprintf( stderr, "Done running tests!\n" );

   return 0;
 }
