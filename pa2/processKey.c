/* 
 * Filename: processKey.c
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Feb 4th, 2019
 * Source of Help: DI slide.
 */

#include <stdio.h>
#include <stdlib.h>
#include "pa2.h"
#include "pa2Strings.h"
#include <string.h>
#include "errno.h"

#define MOVE_THREE 24
#define MOVE_TWO 16
#define MOVE_ONE 8
#define ZERO_FIL 0XFF000000
#define ONE_FIL 0XFF0000
#define TWO_FIL 0XFF00
#define THREE_FIL 0xFF
#define NULL_BYTE '\0'

/*
 * Function Name: processKey()
 * Function Prototype: int processKey( char * str, unsigned char key[] );
 * Description: This function will be used to process key0 and key1
 * Parameters: str - convert to an unsigned int
 *             key[] - storage for byte
 * Side Effect: Prints error information.
 * Error Condition: Number is too large or containing illegal char.
 * Return Value: Return error value or 0 means successful.
 */

 int processKey( char * str, unsigned char key[] ) {
   
   // set local vars
   char *endPtr;
   errno = 0;
   unsigned int convInt;

   // convert str to an unsigned int
   // man -s3 strtoul()
   convInt = strtoul(str, &endPtr, DEF_BASE);
   // check errors
   // number too large, return ERANGE_ERR 
   if( errno == ERANGE ){
     return ERANGE_ERR;
   }
   // check invalid chars, return ENDPTR_ERR
   if( *endPtr != NULL_BYTE ){
     return ENDPTR_ERR;
   }

   //Extract the bytes from the int, storing each byte into the char array key.
   unsigned int zeroIdx;
   unsigned int oneIdx;
   unsigned int twoIdx;
   unsigned int threeIdx;

   // save to key[0]
   zeroIdx = convInt & ZERO_FIL;
   zeroIdx = zeroIdx >> MOVE_THREE;
   key[0] = zeroIdx;

   // save to key[1]
   oneIdx = convInt & ONE_FIL;
   oneIdx = oneIdx >> MOVE_TWO;
   key[1] = oneIdx;

   // save to key[2]
   twoIdx = convInt & TWO_FIL;
   twoIdx = twoIdx >> MOVE_ONE;
   key[KEY_ONE_INDEX] = twoIdx;

   // save to key[3]
   threeIdx = convInt & THREE_FIL;
   key[KEY_TWO_INDEX] = threeIdx;

   return 0;
 }
