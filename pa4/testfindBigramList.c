/*
 * Filename: testfindBigramList.c
 * Author: Zequn Yu
 * UserId: cs30xga
 * Date: Mar 5th, 2019
 * Sources of help: None
 */

#include "pa4.h"
#include "test.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * Unit Test for findBigramList.c
 *
 * gramNode_t * findBigramList( predictTable_t * table, vocab_t * vocab,
 *                        const char * word );
 *
 * Looks for the head node of a linked list in the table that corresponds to
 * the given word.
 *
 * Returns a pointer to the node. If no such node exists, returns NULL.
 */
void testfindBigramList() {
  char * words[] = {
    /* 0 */ "apple",
    /* 1 */ "banana",
    /* 2 */ "carrot",
    /* 3 */ "durian",
    /* 4 */ "elderberry",
    /* 5 */ "fig",
    /* 6 */ "guava",
    /* 7 */ "honeydew"
  };
  size_t numWords = sizeof(words) / sizeof(*words);
  vocab_t vocab = { words, numWords };

  // Set up each bucket's list array.
  gramNode_t listArr0[] = {
    { .index = 0 }, // apple
    { .index = 3 }, // durian
    { .index = 6 }, // guava
  };
  size_t numLists0 = sizeof(listArr0) / sizeof(*listArr0);

  gramNode_t listArr1[] = {
    { .index = 1 }, // banana
    { .index = 4 }, // elderberry
    { .index = 7 }, // honeydew
  };
  size_t numLists1 = sizeof(listArr1) / sizeof(*listArr1);

  gramNode_t listArr2[] = {
    { .index = 2 }, // carrot
    { .index = 5 }, // fig
  };
  size_t numLists2 = sizeof(listArr2) / sizeof(*listArr2);

  gramBucket_t bucketArr[] = {
    { listArr0, numLists0 },
    { listArr1, numLists1 },
    { listArr2, numLists2 },
  };
  size_t numBuckets = sizeof(bucketArr) / sizeof(*bucketArr);

  predictTable_t table = {
    bucketArr,
    numBuckets
  };

  // Look for words that exist, but perhaps in different buckets
  gramNode_t * result;

  // Search for "fig", whose index == 5
  result = findBigramList( &table, 5 );
  TEST( result == &(listArr2[1]) );
  TEST( result->index == 5 );

  // TODO: ADD MORE TEST CASES!

  // Look for nonexistent words
  result = findBigramList( &table, 420 );
  TEST( result == NULL );
}

int main() {
  fprintf( stderr, "Running tests for findBigramList...\n" );
  testfindBigramList();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
} 
