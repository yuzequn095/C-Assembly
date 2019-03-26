/*
 * Filename: pa4Strings.h
 * Author: Zequn Yu
 * UserId: cs30xga
 * Date: Mar 12th, 2019
 * Sources of help: Given.
 */
#ifndef PA4_STRINGS_H
#define PA4_STRINGS_H

// ============================================================================
// Error strings
// ============================================================================
#define STR_ERR_MEM "\n\tMemory limit exceeded.\n\n"

#define STR_ERR_EXTRA_ARG "\n\tExtra argument '%s'.\n\n"

#define STR_ERR_CONVERTING "\n\tConverting '%s' to base '%d'"
#define STR_ERR_NOTINT "\n\t'%s' is not an integer in base '%d'\n\n"
#define STR_ERR_NUM_BUCKETS_BOUND \
  "\n\tnumBuckets (%u) is out of bounds [%u, %u]\n\n"

#define STR_ERR_MISSING_FILE "\n\tMissing the %s required argument.\n\n"
#define STR_VOCAB_FILE "vocabFile"
#define STR_SENTENCE_FILE "sentenceFile"

#define STR_ERR_FILE_OPEN "\n\tCould not open file '%s'"

// ============================================================================
// Usage strings
// ============================================================================
#define STR_USAGE \
  "Usage: %s [-n num] -v vocabFile -s sentenceFile [-h]\n" \
  " -n, --num-buckets=num         Use num as the number of buckets in the\n" \
  "                               prediction table.\n" \
  "                               If not provided, defaults to %u.\n" \
  "                               Must be in the bounds [%u, %u].\n" \
  " -v, --vocab=vocabFile         Use vocabFile as the vocabulary file.\n" \
  " -s, --sentence=sentenceFile   Use sentenceFile as the sentence file.\n" \
  " -h, --help                    Display this help and exit.\n\n"
#define STR_USAGE_SHORT \
  "Usage: %s [-n num] -v vocabFile -s sentenceFile [-h]\n" \
  "See '%s -h' for more details.\n\n"

// EC Constants
#define STR_EC_USAGE \
  "Usage: %s [-n num] [-r seed] -v vocabFile -s sentenceFile [-h]\n" \
  " -n, --num-buckets=num         Use num as the number of buckets in the\n" \
  "                               prediction table.\n" \
  "                               If not provided, defaults to %u.\n" \
  "                               Must be in the bounds [%u, %u].\n" \
  " -r, --rand-seed=seed          Use seed as the RNG seed for 'utter'.\n" \
  " -v, --vocab=vocabFile         Use vocabFile as the vocabulary file.\n" \
  " -s, --sentence=sentenceFile   Use sentenceFile as the sentence file.\n" \
  " -h, --help                    Display this help and exit.\n\n"
#define STR_EC_USAGE_SHORT \
  "Usage: %s [-n num] [-r seed] -v vocabFile -s sentenceFile [-h]\n" \
  "See '%s -h' for more details.\n\n"

// ============================================================================
// Prompt and searching strings
// ============================================================================
#define STR_UNRECOGNIZED_COMMAND "\n\tUnrecognized command '%s'.\n\n"
#define STR_MISSING_ARG "\n\tCommand '%s' missing argument.\n\n"
#define STR_NO_DATA "\n\tNo data for word '%s'.\n\n"

#define STR_COMMAND_HELP \
  "\n" \
  "\tnext  <word>: display the next most likely word for a given word\n" \
  "\tstats <word>: display all words that may follow the given word, \n" \
  "\t              along with their observed counts\n" \
  "\thelp        : display this help message\n" \
  "\n"

#define STR_DELIMS " \t\n"
#define STR_PROMPT ">> "
#define STR_NEXT "\n\t-> %s\n\n"
#define STR_STATS "%10d %s\n"
#define STR_INTERACT_EXIT "bye\n"

// EC Constants
#define STR_EC_COMMAND_HELP \
  "\n" \
  "\tnext  <word>: display the next most likely word for a given word\n" \
  "\tstats <word>: display all words that may follow the given word, \n" \
  "\t              along with their observed counts\n" \
  "\tutter       : utter a random sentence\n" \
  "\thelp        : display this help message\n" \
  "\n"

#define STR_EC_NO_DATA "\n\tNo data available to utter a sentence.\n\n"
#define STR_EC_UTTER_WORD "%s "
#define STR_EC_BEGINNING_OF_SENTENCE "\n\t"
#define STR_EC_END_OF_SENTENCE "\n\n"

#define STR_VOCAB_WORD_COUNT "\n\tLoaded %d word(s) from vocabFile (%s)\n"
#define STR_COUNTING_BIGRAMS "\n\tCounting bigrams from sentenceFile (%s) ... "
#define STR_COUNTING_BIGRAMS_DONE "done!\n"

#endif // PA4_STRINGS_H
