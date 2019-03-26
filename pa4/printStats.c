/*
 * Filename: printStats.c
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Mar 5th, 2019
 * Source of Help: None
 */

#include <stdio.h>
#include <stdlib.h>
#include "pa4.h"
#include "pa4Strings.h"
#include <string.h>
#include <errno.h>

/*
 * Function Name: printStats()
 * Function Prototype: void printStats( gramNode_t * head, vocab_t * vocab )
 * Description: This function will go over linked list and print the count.
 * Side Effects: Print output to stdout.
 * Error Conditions: None.
 * Return Value: None.
 */

 void printStats( gramNode_t * head, vocab_t * vocab ) {

  //check null
  if( head == NULL ) {
    return;
  }

  if( vocab == NULL ) {
    return;
  }

  // set a traverse node
  gramNode_t * curr = head -> next;

  // go traverse
  while( curr ) {
    fprintf( stdout, STR_STATS, curr->count, vocab->words[curr->index] );
    curr = curr -> next;
  }
  
 }
