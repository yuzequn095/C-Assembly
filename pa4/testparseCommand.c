/*
 * Filename: testparseCommand.c
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Mar 5th, 2019
 * Source of Help: None
 */

 #include "pa4.h"
 #include "test.h"
 #include <stdio.h>
 #include <string.h>

/*
 * Unit Test for parseCommand.c
 * 
 * int parseCommand( const char * commandStr, const char * commands[] )
 *
 * Compare if the index returned correct.
 */

 void testparseCommand() {
   const char * commands[] = { "a", "b", "c", "d", "e" };
   const char * c1 = "a";
   TEST( parseCommand( c1, commands ) == 0 );
 
   const char * c2 = "c";
   TEST( parseCommand( c2, commands ) == 2 );

   const char * c3 = "f";
   TEST( parseCommand( c3, commands ) == -1 );
 
   const char * c4 = NULL;
   TEST( parseCommand( c4, commands ) == -1 );

   const char * c6[] = {NULL};
   const char * c5 = "c";
   TEST( parseCommand( c5, c6 ) == -1 );
 }

 int main() {
   fprintf( stderr, "Running tests for parseCommand...\n" );
   testparseCommand();
   fprintf( stderr, "Done running tests!\n" );

   return 0;
 }
