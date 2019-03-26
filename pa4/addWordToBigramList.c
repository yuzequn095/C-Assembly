/*
 * Filename: addWordToBigramList.c
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

/*
 * Function Name: addWordToBigramList()
 * Function Prototype: int addWordToBigramList( gramNode_t* bigramListHead,
 *                     int word2Index );
 * Description: This function to build a linked list of bigrams.
 * Side Effects: None.
 * Error Conditon: Memory allocation fails when creaing a new gramNode.
 * Return Values: 0 if successful, -1 if errors.
 */

 int addWordToBigramList( gramNode_t * bigramListHead, int word2Index ) {
   // check NULL
   if( bigramListHead == NULL ) {
     return 0;
   }

   // check if gramNode exists already, if then count++
   // otherwise allocate mempry for a new gramNode with calloc
   // use assembleGram to set node and count = 1, and append to end
   // skip the head node
   gramNode_t * tmp = bigramListHead -> next;
   while( tmp != NULL ) {
     // check if exist
     if( tmp -> index == word2Index ) {
        // increment count
        (tmp -> count)++;
        return 0;
     }
     tmp = tmp -> next;
   }
   
   // if not exist
   // call calloc() for new node
   gramNode_t * newNode = calloc( 1, sizeof(gramNode_t) );
   // check error
   if( newNode == NULL ) {
     return -1;
   }

   // set node 
   assembleGram( newNode, word2Index );
   // increment count
   (newNode -> count)++;
   
   // append
   gramNode_t * app = bigramListHead;
   while( app -> next != NULL ) {
     app = app -> next;
   }
   // append to the last node
   app -> next  = newNode;
   // update head count
   (bigramListHead -> count)++;
   return 0;
 }
