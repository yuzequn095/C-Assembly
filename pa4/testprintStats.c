/*
 * Filename: testprintStats.c
 * Author: Zequn Yu
 * UserId: cs30xga
 * Date: Mar 5th, 2019
 * Sources of help: None
 */

#include "pa4.h"
#include "pa4Strings.h"
#include "test.h"

#include <stdio.h>

/*
 * Unit Test for printStats.c
 *
 * void printStats( gramNode_t * head, vocab_t * vocab );
 *
 * Print to stdout the count and word for each node in head's linked list.
 */
void testprintStats() {
  // Array of words sorted in alphabetical order (indices listed next to words)
  char * testWords[] = {
      "airgonaut",        // 0
      "alabandical",      // 1
      "annomination",     // 2
      "aquabib",          // 3
      "blateration",      // 4
      "chronanagram",     // 5
      "cosmogyral",       // 6
      "filicology",       // 7
      "frenigerent",      // 8
      "fumificate",       // 9
      "hecatologue",      // 10
      "homerkin",         // 11
      "ichthyarchy",      // 12
      "labascate",        // 13
      "logarithmotechny", // 14
      "magastromancy",    // 15
      "rogalian",         // 16
      "rogitate",         // 17
      "sedecuple",        // 18
      "sinapistic",       // 19
      "stibogram",        // 20
      "stiricide"         // 21
  };

  // Set up vocab
  vocab_t vocab;
  vocab.words = testWords;
  vocab.numWords = 22;

  // Set up linked list
  gramNode_t head, word1, word2, word3, word4, word5;
  head.index  = 14;    // logarithmotechny
  head.count  = 5;
  word1.index = 5;     // chronanagram
  word1.count = 30;
  word2.index = 17;    // rogitate
  word2.count = 777;
  word3.index = 13;    // labascate
  word3.count = 9;
  word4.index = 11;    // homerkin
  word4.count = 420;
  word5.index = 7;     // filicology
  word5.count = 11;

  // Connect the nodes in the linked list
  head.next  = &word1;
  word1.next = &word2;
  word2.next = &word3;
  word3.next = &word4;
  word4.next = &word5;
  word5.next = NULL;
  
  // Test linked list of length 5
  fprintf(stderr, "\nTEST 1: Linked list of length 5\n");
  fprintf(stderr, "-----------------------------------\n");
  // Print the expected results
  fprintf(stderr, "Expected results:\n");
  printf(STR_STATS, 30, "chronanagram");
  printf(STR_STATS, 777, "rogitate");
  printf(STR_STATS, 9, "labascate");
  printf(STR_STATS, 420, "homerkin");
  printf(STR_STATS, 11, "filicology");
  fprintf(stderr, "\n");
  // Print the actual results
  fprintf(stderr, "Actual results:\n");
  printStats(&head, &vocab);
  fprintf(stderr, "\n");

  // TODO: ADD MORE TEST CASES!
  head.index  = 1;
  head.count = 1;
  word1.index = 2;
  word1.count = 2;
  word2.index = 3;
  word2.count = 3;
  head.next  = &word1;
  word1.next = &word2;
  word2.next = NULL;
  fprintf(stderr, "\nTEST 2: Linked list of length 2\n");
  fprintf(stderr, "-----------------------------------\n");
  fprintf(stderr, "Expected results:\n");
  printf(STR_STATS, 2, "annomination");
  printf(STR_STATS, 3, "aquabib");
  fprintf(stderr, "\n");
  fprintf(stderr, "Actual results:\n");
  printStats(&head, &vocab);
  fprintf(stderr, "\n");
}

int main() {
  fprintf(stderr, "Running tests for printStats...\n");
  testprintStats();
  fprintf(stderr, "Done running tests!\n");

  return 0;
}
