/*
 * Filename: parseCommand.c
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Mar 5th, 2019
 * Source of Help: None.
 */

#include <stdio.h>
#include <stdlib.h>
#include "pa4.h"
#include "pa4Strings.h"
#include <string.h>
#include <errno.h>

/*
 * Function Name: parseCommand()
 * Function Prototype: int parseCommand( const char * commandStr, 
 *                                       const char * command[] )
 * Description: parse command string entered to check if valid.
 * Side Effects: None.
 * Error Condition: None.
 * Return Value: return index or -1 if not in commands.
 */

 int parseCommand( const char * commandStr, const char * commands[] ) {

   // NULL check
   if( commandStr == NULL ) {
     return -1;
   }
   if( commands == NULL ) {
     return -1;
   }

   // while loop for commands
   int idx = 0;
   int same = 1;
   
   while( commands[idx] != NULL ) {
     // check if same
     if( strcmp( commandStr, commands[idx] ) == 0 ) {
       // same 
       same = 0;
       break;
     }
     // update index
     idx++;
   }
   
   // check not exist
   if( same == 1 ) {
     return -1;
   }
   return idx;
 }
