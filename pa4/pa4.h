/*
 * Filename: pa4.h
 * Author: Zequn Yu
 * UserId: cs30xga
 * Date: Mar 12th, 2019
 * Sources of help: Given.
 */
#ifndef PA4_H
#define PA4_H

#include <stdio.h>
#include <stddef.h>

// =============================================================================
// Constants
// =============================================================================

// Feel free to add your own constants (:

// Command line parsing.
#define SHORT_OPTSTRING  "n:v:s:h"
#define NUM_BUCKETS_FLAG 'n'
#define VOCAB_FLAG       'v'
#define SENTENCE_FLAG    's'
#define HELP_FLAG        'h'
#define NUM_BUCKETS_LONG "num-buckets"
#define VOCAB_LONG       "vocab"
#define SENTENCE_LONG    "sentence"
#define HELP_LONG        "help"

#define NUM_BUCKETS_BASE 10
#define MIN_NUM_BUCKETS  1
#define MAX_NUM_BUCKETS  101

// Default values.
#define DEFAULT_NUM_BUCKETS 7

// Constants used in the interactive portion of the program.
#define COMMANDS { "help", "next", "stats", NULL }
#define HELP_IDX  0
#define NEXT_IDX  1
#define STATS_IDX 2

// EC constants
#define EC_COMMANDS { "help", "next", "stats", "utter", NULL }
#define EC_UTTER_IDX 3

#define EC_SHORT_OPTSTRING "n:r:v:s:h"
#define EC_RAND_SEED_FLAG 'r'
#define EC_RAND_SEED_BASE 10

// =============================================================================
// Struct Definitions
// =============================================================================

struct gramNode {
  // Index into the vocab array representing the gram.
  unsigned int index;     

  // How many times this gram occurs in the given text.
  // If this gram is the head node of the list, it is the number of grams in the
  // linked list (excluding the head).
  unsigned int count;     
                         
  // Pointer to the next node in the linked list.   
  struct gramNode * next;
};
typedef struct gramNode gramNode_t;

struct gramBucket {
  // Pointer to the array of linked list heads.
  gramNode_t * listArr;

  // The number of entries in the array.
  size_t numLists;
};
typedef struct gramBucket gramBucket_t;

struct predictTable {
  // Pointer to the array of buckets in the hashtable.
  gramBucket_t * bucketArr;

  // The number of buckets in the hashtable.
  size_t numBuckets;
};
typedef struct predictTable predictTable_t;

struct vocab {
  // Array of strings (char *).
  char ** words;

  // Number of words in this vocabulary.
  size_t numWords;
};
typedef struct vocab vocab_t;

// =============================================================================
// Function Prototypes
// =============================================================================

void assembleGram( gramNode_t * gram, int wordIndex );
int countBigrams( predictTable_t * table, vocab_t * vocab,
                  FILE * sentenceFile );
gramNode_t * findBigramList( predictTable_t * table, int wordIndex );
int getBucketIndex( int wordIndex, size_t numBuckets );
int getRemainder( int dividend, int divisor );
int gramNodeCmp( const void * p1, const void * p2 );
int addBigramListToBucket( predictTable_t * table,
    int word1Index, int word2Index );
int addWordToBigramList( gramNode_t * bigramListHead, int word2Index );
void interact( predictTable_t * table, vocab_t * vocab );
int isInBounds( int value, int minBound, int maxBound );
int loadVocabulary( vocab_t * vocab, FILE * vocabFile );
gramNode_t * getMaxWord( gramNode_t * head );
int parseCommand( const char * commandStr, const char * commands[] );
void printStats( gramNode_t * head, vocab_t * vocab );
int strPtrCmp( const void * p1, const void * p2 );
int wordToIndex( const char * word, vocab_t * vocab );

// EC functions.
void utter( predictTable_t * table, vocab_t * vocab );

#endif // PA4_H
