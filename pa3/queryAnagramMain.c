/*
 * Filename: queryAnagramMain.c
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Feb 27th, 2019
 * Source of Help: None.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>
#include "pa3.h"
#include "pa3Strings.h"

#define DOT_EXT '.'
#define NEW_LINE '\n'
#define NULL_CHAR '\0'
/* 
 * Function Name: main ()
 * Function prototype: int main( int argc, char *argv[] );
 * Description: This function driver for the query program. 
 *              Its main tasks are to parse the command line arguments
 *              and enter interactive mode.
 * Parameters: argc - number of command line passed in.
 *              argv - command line arguments passed in.
 * Side Effects: Pritins information to stdout or stderr.
 * Error Conditions: Unknown flag; too many command line; wrong tableSize
 *                   Anagram filename not provided; anagram file no entesion
 *                   can't allocate memory
 * Return value: EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */

int main( int argc, char *argv[] ) {
 
  // parse the command line
  int c;
  const char *anaFilename;
  char *tableSize;

  // use getopt to parse the flags described in the long usage stmt
  while( (c = getopt( argc, argv, QUERY_ARG_STR )) != -1 ) {
    
    switch( c ){
      case ANAGRAM_FILE_FLAG: // case for anagram filename
        // save the anagram file
        anaFilename = optarg;
        break;

      case SIZE_FLAG:  // case for table size
        // save the size 
        tableSize = optarg;
        break;

      case HELP_FLAG: // case for NONE
        fprintf( stdout, STR_QUERY_USAGE_LONG, argv[0], QUERY_TABLE_MIN_SIZE,
                 QUERY_TABLE_MAX_SIZE, QUERY_TABLE_DEFAULT_SIZE );
        return EXIT_SUCCESS;

      default: // invalid flags or missing
        fprintf( stderr, STR_QUERY_USAGE_SHORT, argv[0], argv[0] );
        return EXIT_FAILURE;
    }
  } 
  
  // if extra arguments
  if( optind < argc ) {
    fprintf( stderr, STR_ERR_EXTRA_ARGS, argv[0] );
    fprintf( stderr, STR_QUERY_USAGE_SHORT, argv[0], argv[0] );
    return EXIT_FAILURE;
  }

  // convert size from string in base 10 to unsigned int
  errno = 0;
  char *ptr;
  unsigned int longSize;
  if( tableSize == NULL){
    longSize = QUERY_TABLE_DEFAULT_SIZE;
  }
  else{
    longSize = strtoul( tableSize, &ptr, BASE );
  }
  // too big
  if( errno != 0 ) {
    char buf[BUFSIZ];
    snprintf( buf, BUFSIZ, STR_ERR_CONVERTING, tableSize, BASE );
    perror( buf );
    fprintf( stderr, "%s", STR_NEWLINE_CHAR );
    return EXIT_FAILURE;
  }

  // not an int
  if( *ptr != NULL_CHAR ) {
    fprintf( stderr, STR_ERR_NOTINT, tableSize, BASE );
    return EXIT_FAILURE;
  }

  // check table size
  int sizeRet;
  sizeRet = isInBounds( longSize, QUERY_TABLE_MIN_SIZE, QUERY_TABLE_MAX_SIZE );
  if( sizeRet != 1 ) {
    fprintf( stderr, STR_ERR_TABLE_SIZE_BOUNDS, longSize, 
             QUERY_TABLE_MIN_SIZE, QUERY_TABLE_MAX_SIZE );
    return EXIT_FAILURE;
  }
  
  // check filename
  if( anaFilename == NULL ) {
    fprintf( stderr, STR_ERR_FILENAME_NOT_ENTERED );
    return EXIT_FAILURE;
  }

  // validate .ano
  char *retValue;
  retValue = strchr( anaFilename, DOT_EXT );
  if( retValue == NULL ) {
    fprintf( stderr, STR_ERR_ANAGRAM_FILE_EXT, ANAGRAM_FILE_EXT );
    return EXIT_FAILURE;
  }
  int cmpValue;
  cmpValue = strncmp( retValue, ANAGRAM_FILE_EXT, ANAGRAM_FILE_EXT_LEN );
  if( cmpValue != 0 ) {
    fprintf( stderr, STR_ERR_ANAGRAM_FILE_EXT, ANAGRAM_FILE_EXT );
    return EXIT_FAILURE;
  }
  
  // build queryTable
  // use calloc to zero-fill the memory for array of bucket_t
  bucket_t *memBuc;
  queryTable_t *memQue;
  memBuc = calloc( longSize, sizeof(bucket_t) );
  
  // if successful, allocate the queryTable_t and initialize ite members
  if( memBuc != NULL ) {
    memQue = calloc( 1, sizeof(queryTable_t) );
    if( memQue == NULL ) {
      free(memBuc);
      free(memQue);
      fprintf( stderr, STR_ERR_MEM );
      return EXIT_FAILURE;
    }
  }
  // if not successful, print error
  else{
    free(memBuc);
    fprintf( stderr, STR_ERR_MEM );
    return EXIT_FAILURE;
  }
  memQue -> size = longSize;
  memQue -> tablePtr = memBuc;

  // load anagrams into queryTable
  int loadErr = loadQueryTable( anaFilename, memQue );
  if( loadErr == -1 ) {
    return EXIT_FAILURE;
  }
  
  // call loop 
  queryLoop( memQue );

  // free
  for( int i = 0; i < memQue -> size; i++ ) {
    free(memQue -> tablePtr[i].dataPtr);
  }
  free(memQue -> tablePtr);
  free(memQue);
  return EXIT_SUCCESS;
}
