/*
 * Filename: addBigramListToBucket.c
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Mar 12th, 2019
 * Source of Help: Di, Piazza
 */

#include <stdio.h>
#include <stdlib.h>
#include "pa4.h"
#include "pa4Strings.h"
#include <string.h>
#include <errno.h>

/*
 * Function Name: addBigramListToBucket()
 * Function Prototype: int addBigramListToBucket( predictTable_t * table,
 *                                                int word1Index,
 *                                                int word2Index );
 * Description: This function creates a new bigram list.
 * Side Effects: None.
 * Error Conditions: Memory error when expanding or when adding.
 * Return Value: 0 if successfil, -1 if error.
 */

 int addBigramListToBucket( 
     predictTable_t * table, int word1Index, int word2Index ) {
   // create a new bigram list for word at w1idx in the table bucket
   // how to get idx in table->bucketArr: getBucketIndex( w1idx, table->num)
   // Piazza: how to realloc
   // get idx
   int idx = getBucketIndex( word1Index, table -> numBuckets );
   // realloc
   gramBucket_t *bucketPtr = (table -> bucketArr) + idx;
   gramNode_t *tmpPtr = NULL;
   tmpPtr = realloc( bucketPtr->listArr, 
                  (bucketPtr->numLists)*sizeof(gramNode_t)+sizeof(gramNode_t));
   // check fail
   if( tmpPtr == NULL ) {
     return -1;
   }
   // re-assign and set
   bucketPtr -> listArr = tmpPtr;
   (bucketPtr -> numLists)++;
   size_t tmpNum = bucketPtr -> numLists;
   // find the bucket where w1idx's node goes, and realloc to expand
   // create a new node for word at w1idx as head of list, with assemble
   gramNode_t *newHead = &(bucketPtr->listArr[tmpNum-1]);
   assembleGram( newHead, word1Index );
   // add word at w1idx to list using addwordtobiglist
   int ret = addWordToBigramList( newHead, word2Index);
   // check fail
   if( ret == -1 ) {
     return -1;
   }

   // qsort
   qsort( bucketPtr->listArr, bucketPtr->numLists, 
          sizeof(gramNode_t), gramNodeCmp );
   
   // successful
   return 0;
 }
