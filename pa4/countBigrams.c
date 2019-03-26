/*
 * Filename: countBigrams.c
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

#define NEW_LINE '\n'
#define NULL_CHAR '\0'

/*
 * Function Name: countBigrams()
 * Function Prototype: int countBigrams( predictTable_t * table, 
 *                                       vocab_t * vocab, 
 *                                       FILE * sentenceFile );
 * Description: This function counts all bigram and store information.
 * Side Effects: None.
 * Error Condition: Memory allocation error.
 * Return Value: 0 if successful, -1 if error.
 */

 int countBigrams( 
     predictTable_t * table, vocab_t * vocab, FILE * sentenceFile ) {
   // check NULL
   if( table == NULL  ) {
     return 0;
   }
   if( vocab == NULL ) {
     return 0;
   }
   if( sentenceFile == NULL ) {
     return 0;
   }
   
   char buffer[BUFSIZ];
   char w1[BUFSIZ];
   char w2[BUFSIZ];
   char *nl;
   int word = 1;
   int w1Idx;
   int w2Idx;

   // read in bigram(w1, w2) from file 
   // replace newline with null
   // get idx of each word in vocab using wordToIndex
   
   // retrieve the bigram list of w1 using findBL()
   // add w2 to list using addWTB()
   // if not list exists, create a new one using addBLTB()

   // w2 to be new w1 in bigram, read in a new word  to be w2
   // continue step2 until end of FILE
   while( fgets( buffer, BUFSIZ, sentenceFile ) != NULL ) {
     // check if too long
     int tooLong = 1;

     // for word1
     if( word == 1 ) {
       // null each word
       nl = strchr( buffer, NEW_LINE );
       // check new line
       if( nl != NULL ) {
         *nl = NULL_CHAR;
         tooLong = 0;
       }
       // allocate space for word
       if( tooLong != 0 ) {
         buffer[BUFSIZ-1] = NULL_CHAR;
       }
       // set w1
       //w1 = buffer;
       int w1Null = 0;
       int i = 0;
       while( w1Null == 0 ) {
         w1[i] = buffer[i];
         if( buffer[i] == NULL_CHAR ) {
           break;
         }
         i++;
       }
       // get index
       w1Idx = wordToIndex( w1, vocab );
       // check idx error
       if( w1Idx == -1 ) {
         continue;
       }
       // update word type
       word = 2;
       continue;
     }// word1 ends

     // for word 2
     if( word == 2 ) {
       // null each word
       nl = strchr( buffer, NEW_LINE );
       // check new line
       if( nl != NULL ) {
         *nl = NULL_CHAR;
         tooLong = 0;
       }
       // allocate space for word
       if( tooLong != 0 ) {
         buffer[BUFSIZ-1] = NULL_CHAR;
       }
       // set w2
       //w2 = buffer;
       int w2Null = 0;
       int j = 0;
       while( w2Null == 0 ) {
         w2[j] = buffer[j];
         if( buffer[j] == NULL_CHAR ) {
           break;
         }
         j++;
       }
       // get index
       w2Idx = wordToIndex( w2, vocab );
       // check idx error
       if( w2Idx == -1 ) {
         word = 1;
         continue;
       }
     }// word2 ends
     
     // rest of function
     // get bigram list of word1 using findBigramList()
     gramNode_t * tmpNode = findBigramList( table, w1Idx );
     // check if not exists
     if( tmpNode == NULL ) {
       // create a new list
       addBigramListToBucket( table, w1Idx, w2Idx );
     }
     else{
       // add word2
       addWordToBigramList( tmpNode, w2Idx );
     }

     // repeat
     //w1 = w2;
     int m;
     for(  m = 0; m < sizeof(w2); m++ ) {
       w1[m] = w2[m];
       if( w2[m] == NULL_CHAR ){
         break;
       }
     }
     w1Idx = w2Idx;
     // for next detect
     // clear old w2
     for( int n = 0; n < sizeof(w2); n++ ) {
       w2[n] = NEW_LINE;
     }
     for( int k = m+1; k < sizeof(w1); k++ ) {
       w1[k] = NEW_LINE;
     }
   
   }// while ends

   return 0;
 }
