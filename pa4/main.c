/*
 * Filename: main.c
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Mar 12th, 2019
 * Source of Help: None.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>
#include "pa4.h"
#include "pa4Strings.h"
#define STR_NEWLINE_CHAR "\n"
#define NULL_CHAR '\0'

/*
 * Function Name: main()
 * Function prototype: int main( int argc, char * argv[] );
 * Description: This function will driver the program.
 * Parameters: argc - the number of command line passed in.
 *             argv - command line arguments passed in.
 * Side Effect: Print output to stdout or stderr.
 * Error Condition: Unknown flag, too many command line, num-buckets, 
 *                  wrong file, memory allocated error, function return error
 * Return value: EXIT_SUCCESS if successful, EXIT_FAILURE if error.
 */

 static struct option options[] = {
   {HELP_LONG, no_argument, NULL, HELP_FLAG},
   {NUM_BUCKETS_LONG, required_argument, NULL, NUM_BUCKETS_FLAG},
   {VOCAB_LONG, required_argument, NULL, VOCAB_FLAG},
   {SENTENCE_LONG, required_argument, NULL, SENTENCE_FLAG},
   {0, 0, 0, 0}
 };

 int main( int argc, char * argv[] ) {
   // parse command line with getopt_long
   int c;
   char *bucketNum = NULL;
   char *vocabFile = NULL;
   char *senFile = NULL;

   // use getopt
   while((c=getopt_long( argc, argv, SHORT_OPTSTRING, options, NULL)) != -1){
     switch( c ) {
       // help case
       case HELP_FLAG:
         fprintf( stdout, STR_USAGE, argv[0], DEFAULT_NUM_BUCKETS, 
                  MIN_NUM_BUCKETS, MAX_NUM_BUCKETS );   
         return EXIT_SUCCESS;
         break;
       
       // num-bucket case
       case NUM_BUCKETS_FLAG:
         bucketNum = optarg;
         break;

       // vocab case
       case VOCAB_FLAG:
         vocabFile = optarg;
         break;

       // sentence case
       case SENTENCE_FLAG:
         senFile = optarg;
         break;
     
       // invalid or missing
       default:
         fprintf( stderr, STR_USAGE_SHORT, argv[0], argv[0] );
         return EXIT_FAILURE;
         break;
     }
   }// while ends
   
   // extra
   if( optind < argc ) {
     fprintf( stderr, STR_ERR_EXTRA_ARG, argv[optind] );
     fprintf( stderr, STR_USAGE_SHORT, argv[0], argv[0] );
     return EXIT_FAILURE;
   }

   // check file name
   if( vocabFile == NULL ) {
     fprintf( stderr, STR_ERR_MISSING_FILE, STR_VOCAB_FILE );
     fprintf( stderr, STR_USAGE_SHORT, argv[0], argv[0] );
     return EXIT_FAILURE;
   }
   if( senFile == NULL ) {
     fprintf( stderr, STR_ERR_MISSING_FILE, STR_SENTENCE_FILE );
     fprintf( stderr, STR_USAGE_SHORT, argv[0], argv[0] );
     return EXIT_FAILURE;
   }
   // convert num_bucket
   //errno = 0;
   //char *ptr;
   size_t numBucket;
   if( bucketNum == NULL ) {
     numBucket = DEFAULT_NUM_BUCKETS;
   }
   else{
     errno = 0;
     char *ptr;
     numBucket = strtoul( bucketNum, &ptr, NUM_BUCKETS_BASE );
   //}
     // too-big
     if( errno != 0 ) {
       char buf[BUFSIZ];
       snprintf( buf, BUFSIZ, STR_ERR_CONVERTING, bucketNum, NUM_BUCKETS_BASE );
       perror( buf );
       fprintf( stderr, "%s", STR_NEWLINE_CHAR );
       return EXIT_FAILURE;
     }
     // not int
     if( *ptr != NULL_CHAR ) {
       fprintf( stderr, STR_ERR_NOTINT, bucketNum, NUM_BUCKETS_BASE );
       return EXIT_FAILURE;
     }
     // not in bounds
     if( isInBounds( numBucket, MIN_NUM_BUCKETS, MAX_NUM_BUCKETS ) != 1 ) {
       fprintf( stderr, STR_ERR_NUM_BUCKETS_BOUND, numBucket, MIN_NUM_BUCKETS,
                MAX_NUM_BUCKETS );
       return EXIT_FAILURE;
     }
   }
   // open vocab file and sent file use fopen
   FILE *vf;
   FILE *sf;
   vf = fopen( vocabFile, "rb" );
   sf = fopen( senFile, "rb" );
   if( vf == NULL ) {
     fprintf( stderr, STR_ERR_FILE_OPEN, vocabFile );
     return EXIT_FAILURE;
   }
   if( sf == NULL ) {
     fprintf( stderr, STR_ERR_FILE_OPEN, senFile );
     return EXIT_FAILURE;
   }

   // build predictTable
   // allocate
   predictTable_t table;
   table.bucketArr = calloc( numBucket, sizeof(gramBucket_t) );
   //gramBucket_t *bucket = calloc(1, sizeof(gramBucket_t));
   // check errors
   //if( bucket == NULL ) {
   if( table.bucketArr == NULL ){  
     fprintf( stderr, STR_ERR_MEM );
     return EXIT_FAILURE;
   }
   //predictTable_t *table = NULL;
   //table -> bucketArr = bucket;
   //table -> numBuckets = 1;
   table.numBuckets = numBucket;
   
   // build vocab
   vocab_t vocab;
   int ret = loadVocabulary( &vocab, vf );
   // no errors
   if( ret == 0 ) {
     fprintf( stdout, STR_VOCAB_WORD_COUNT, vocab.numWords, vocabFile );
   }
   // errors
   else{
     free(table.bucketArr);
     return EXIT_FAILURE;
   }

   // count bigrams
   fprintf( stdout, STR_COUNTING_BIGRAMS, senFile );
   int retc = countBigrams( &table, &vocab, sf );
   // no errors
   if( retc == 0 ) {
     fprintf( stdout, STR_COUNTING_BIGRAMS_DONE );
   }
   // errors
   else{
     free(table.bucketArr);
     return EXIT_FAILURE;
   }

   // enter interactive
   interact( &table, &vocab );

   // free
   // free array pointered by table pointer
   for( int i = 0; i < table.numBuckets; i++ ) {
     // free array pointered by bucket pointer
     for( int j = 0; j < table.bucketArr[i].numLists; j++ ) {
       // free each node 
       // get the first node
       gramNode_t * cur = &(table.bucketArr[i].listArr[j]);
       gramNode_t * next;
       // loop for each node
       do{
         next = cur -> next;
         free(next);
         cur = next;
       }while(next != NULL);//do-while ends
       // free 'cur'
     }
     free( table.bucketArr[i].listArr);
   }
     free( table.bucketArr );
   

   return EXIT_SUCCESS;
 }
