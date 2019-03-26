/*
 * Filename: getMaxWord.c
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
 * Function Name: getMaxWord)
 * Function Prototype: gramNode_t * getMaxWord( gramNode_t * head );
 * Description: This is a helper function to fine the highest count node.
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: Null if no node in linked list, otherwise return pointer to
 *               highest count.
 */

 gramNode_t * getMaxWord( gramNode_t * head ) {
   
   // check null
   if( head == NULL || head->next == NULL) {
     return NULL;
   }
   
   // set local
   gramNode_t *tmp;
   gramNode_t * curr = head -> next;

   unsigned int max = 0;
   // go over
   while( curr ) {
     // if counter a bigger count
     if( curr->count > max ) {
       // update
       max = curr->count;
       tmp = curr;
     }
     // update curr
     curr = curr->next;
   }
   
   return tmp;
 }
