/*
 * Filename: findBigramList.c
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
 * Function Name: findBigramList()
 * Function Prototype: gramNode_t * findBigramList( predictTable_t * table,
 *                                                  int wordIndex );
 * Description: This function finds the head of linked list to the given idx.
 * Side Effect: None.
 * Error Condition: None.
 * Return Value: the head node or NULL if not exist.
 */
 
 gramNode_t * findBigramList( predictTable_t * table, int wordIndex ) {
   // check edge case
   if( wordIndex == -1 ) {
     return NULL;
   }

   // find gramBucket_t contains the word using getBucketIndex()
   int idx = getBucketIndex( wordIndex, table -> numBuckets );
   
   // search for gramNode_t match idx in bucket using bsearch
   // make tmpNode using assembleGram
   gramNode_t temp;
   assembleGram( &temp, wordIndex );
   gramNode_t * searchNode;
   searchNode = bsearch( &temp, table->bucketArr[idx].listArr,
                         table->bucketArr[idx].numLists,
                         sizeof(gramNode_t), gramNodeCmp );
   // if can't search target
   if( searchNode == NULL ) {
     return NULL;
   }
   return searchNode;
 }
