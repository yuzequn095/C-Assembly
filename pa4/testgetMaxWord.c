/*
 * Filename: testgetMaxWord.c
 * Author: Zequn Yu
 * UserId: cs30xga
 * Date: Mar 5th, 2019
 * Source of Help: None
 */

#include "pa4.h"
#include "pa4Strings.h"
#include "test.h"
#include <stdio.h>

/*
 * Unit Test for getMaxWord.c
 *
 * gramNode_t * getMaxWord( gramNode_t * head );
 *
 * Print the correct count.
 */

 void testgetMaxWord() {
   // Test cases
   gramNode_t h1, w1, w2;
   h1.index = 0;
   h1.count = 4;
   w1.index = 1;
   w1.count = 3;
   w2.index = 2;
   w2.count = 7;
   h1.next = &w1;
   w1.next = &w2;
   w2.next = NULL;
   gramNode_t * ret = getMaxWord( &h1 );
   TEST( ret->index == 2 );  
  
   h1.index = 0;
   h1.count = 11;
   w1.index = 1;
   w1.count = 3;
   w2.index = 2;
   w2.count = 7;
   h1.next = &w1;
   w1.next = &w2;
   w2.next = NULL;
   ret = getMaxWord( &h1 );
   TEST( ret->index == 2 );

   h1.index = 0;
   h1.count = 11;
   w1.index = 1;
   w1.count = 13;
   w2.index = 2;
   w2.count = 7;
   h1.next = &w1;
   w1.next = &w2;
   w2.next = NULL;
   ret = getMaxWord( &h1 );
   TEST( ret->index == 1 );

   gramNode_t hn;
   hn.next = NULL;
   ret = getMaxWord( &hn );
   TEST( ret == NULL );
 
 }

 int main() {
   fprintf( stderr, "Running tests for getMaxWord...\n" );
   testgetMaxWord();
   fprintf( stderr, "Done running tests!\n" );

   return 0;
 }
