/*
 * Filename: processPassphrase.c
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Feb 12th, 2019
 * Source of Help: Di slide.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include "pa2.h"
 #include "pa2Strings.h"
 #include <string.h>
 #include "errno.h"

 #define NULL_BYTE '\0'
/*
 * Function Name: processPassphrase()
 * Function Prototype: int processPassphrase( char * str, unsigned char *
 *                                            passphrase );
 * Description: Process the passphrase from the command line arguments.
 * Parameters: str - the str input
 *             passphrase - converted str to passphrase
 * Side Effect: Print error or correct infomation.
 * Error Condition: If str is not in bounds.
 * Return Value: Return error value or return 0 (sucessfully).
 */

 int processPassphrase( char * str, unsigned char * passphrase ) {
   // Set local var
   //int lenStr = 0;
   //for( int m = 0; m < MAX_PASSPHRASE_SIZE + 1; m++ ) {
     //if( *(str + m ) != NULL_BYTE ){
       //lenStr = lenStr + 1;
     //}
     //else{
       //break;
     //}
   //}
   int lenStr = strlen(str);
   // Check if str in bounds
   if( isInBounds( lenStr, MIN_PASSPHRASE_SIZE, MAX_PASSPHRASE_SIZE) == 0 ) {
     return LENGTH_ERR;
   }

   // No errors
   for( int i = 0; i < lenStr; i++ ) {
     //if not null byte
     if( *(str + i) != NULL_BYTE ) {
       *(passphrase + i) = *(str + i);
     }
     //if null byte
     else {
       break;
     }
   }
   
   // check if shorter
   if( lenStr < MAX_PASSPHRASE_SIZE ) {
     //copy backward
     for( int j = lenStr; j < (MAX_PASSPHRASE_SIZE ); j++ ) {
       *(passphrase + j) = *( str + lenStr - 1 );
       lenStr = lenStr - 1;
     }
   } 

   return 0;
 }
