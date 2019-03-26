/* 
 * Filename: testprocessRotateValue.c
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Feb 5th, 2019
 * Source of Help: None
 */

#include <stdio.h>
#include "pa2.h"
#include "test.h"

/*
 * Unit Test for processRotateValue.s
 *
 * int processRotateValue( char * str, int * rotateValue );
 * 
 * Checks the return value and value of variable
 *
 * The value is correct then function is corrent
 */

void testprocessRotateValue( ) {
  
  /* TEST CASES */
  char *str1 = "12";
  int v1;
  TEST( processRotateValue(str1, &v1) == 0 );
  //int res = processRotateValue(str1, &v1);
  //TEST( res == 0 );
  TEST( v1 == 12 );

  char *str2 = "13aa";
  int v2 = 0;
  TEST( processRotateValue(str2, &v2) == 0 );
  TEST( v2 == 13 );

  char *str3 = "66abc";
  int v3;
  //TEST( processRotateValue(str3, &v3) == 0 );
  int res = processRotateValue(str3, &v3);
  TEST( res == -3 );
  TEST( v3 == 66 );

  char *str4 = "999999999999999999999999999999";
  int v4;
  //TEST( processRotateValue(str4, &v4) == -2 );
  int res1 = processRotateValue(str4, &v4);
  TEST( res1 == -2 );

  char *str5 = "abcdad";
  int v5;
  TEST( processRotateValue(str5, &v5) == -1 );
}

int main ( void ) {
  
  fprintf(stderr, "Running tests for processRotateValue...\n");
  testprocessRotateValue();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
