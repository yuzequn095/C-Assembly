/*
 * Filename: interact.c
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Mar 12th, 2019
 * Source of Help: None.
 */

#include <stdio.h>
#include <stdlib.h>
#include "pa4.h"
#include "pa4Strings.h"
#include <string.h>
#include <errno.h>
#include <ctype.h>

/*
 * Function Name: interact()
 * Function Prototype: void interact( predictTable_t * table, 
 *                                    vocab_t * vocab );
 * Description: This function handles the user interaction.
 * Side Effects: Will print output to stdout.
 * Error Condition: No word entered, command invalid.
 * Return Value: None.
 */

 void interact( predictTable_t * table, vocab_t * vocab ) {
   // print out help
   fprintf( stdout, STR_COMMAND_HELP );

   // print prompt
   fprintf( stdout, STR_PROMPT );

   // get input from user
   char buffer[BUFSIZ];
   while( fgets(buffer, BUFSIZ, stdin) ) {
     // parse the command entered
     // strtok
     // empty -> reprompt
     // convert to lowercase
     // call parsecommand
     // not valid -> print
     const char delimiter[] = STR_DELIMS;
     char *token;
     token = strtok( buffer, delimiter );
     // empty
     if( token == NULL ) {
       fprintf( stdout, STR_PROMPT );
     }
     // to lower case
     for( int i = 0; token[i]; i++ ) {
       token[i] = tolower(token[i]);
     }
     
     char *comm = token;

     // parseCommand
     const char * commArr[] = COMMANDS;
     int ret = parseCommand( token, commArr );
     // not valid
     if( ret == -1 ) {
       fprintf( stdout, STR_UNRECOGNIZED_COMMAND, token );
       fprintf( stdout, STR_PROMPT );
       continue;
     }
       
     // parse the word
     token = strtok( NULL, delimiter );
     
     // next case
     if( strcmp(comm, commArr[NEXT_IDX]) == 0 ) {
       // check word 
       if( token == NULL ) {
         fprintf( stdout, STR_MISSING_ARG, comm );
         fprintf( stdout, STR_PROMPT );
         continue;
       }
       // find the list 
       int idx = wordToIndex( token, vocab );
       gramNode_t * tmpNode = findBigramList( table, idx ); 
       // if not found
       if( tmpNode == NULL ) {
         fprintf( stdout, STR_NO_DATA, token );
         fprintf( stdout, STR_PROMPT );
         continue;
       }
       // search 
       gramNode_t * targetNode = getMaxWord( tmpNode );
       fprintf( stdout, STR_NEXT, vocab->words[targetNode->index] );
     }
     
     // stats case
     else if( strcmp( comm, commArr[STATS_IDX]) == 0 ) {
       // check word
       if( token == NULL ) {
         fprintf( stdout, STR_MISSING_ARG, comm );
         fprintf( stdout, STR_PROMPT );
         continue;
       }
       // find the list
       int idx = wordToIndex( token, vocab );
       gramNode_t * tmpNode = findBigramList( table, idx );
       // if not found
       if( tmpNode == NULL ) {
         fprintf( stdout, STR_NO_DATA, token );
         fprintf( stdout, STR_PROMPT );
         continue;
       }
       // print
       printStats( tmpNode, vocab );
     }
     
     // help case
     else if( strcmp( comm, commArr[HELP_IDX]) == 0 ) {
       // print
       fprintf( stdout, STR_COMMAND_HELP );
     }

     // otheres
     else{
       ;
     }

     // prompt for next loop
     fprintf( stdout, STR_PROMPT );
   }
 
   // when end
   fprintf( stdout, STR_INTERACT_EXIT );
 }

