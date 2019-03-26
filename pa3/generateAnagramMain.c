/*
 * Filename: generateAnagamMain.c
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
#include <ctype.h>

#define DOT_EXT '.'
/*
 * Function Name: main
 * Function prototype: int main( int argc, char *argv[] )
 * Description: This function will drive the main behavior of generating
 *              the anagrams from the input file.
 * Parameters: argc - the number of command line passed in
 *             argv - the content passed in
 * Side Effects: It may output to stderr or stdout.
 * Error Condistion: Unknown flag, too many command line, not end ".ano"
 *                   error in function
 * Return Value: EXIT_FAILUER on error, EXIT_SUCCESS on success
 */
 



int main( int argc, char *argv[] ) {
  
  int c;
  const char *inFilename = IN_FILE_DEFAULT;
  const char *outFilename = OUT_FILE_DEFAULT;

  // use getopt to parse the flags  
  while( (c = getopt( argc, argv, GENERATE_ARG_STR )) != -1 ) {
    
    switch( c ) {
      case IN_FILE_FLAG: // case for inputname
        inFilename = optarg; // save the input file name
        break;

      case OUT_FILE_FLAG: // case for outputname
        outFilename = optarg; // save the output file name
        break;

      case HELP_FLAG: // case for NONE
        fprintf( stdout, STR_GENERATE_ANAGRAM_USAGE_LONG, argv[0], 
                 IN_FILE_DEFAULT, ANAGRAM_FILE_EXT, OUT_FILE_DEFAULT );
        return EXIT_SUCCESS;

      default: // not ont of the above flags
        fprintf( stderr, STR_GENERATE_ANAGRAM_USAGE_SHORT, argv[0], argv[0] );
        return EXIT_FAILURE;
    }
  }
  
  // if extra arguments
  if( optind < argc ) {
    fprintf( stderr, STR_ERR_EXTRA_ARGS, argv[0] );
    fprintf( stderr, STR_GENERATE_ANAGRAM_USAGE_SHORT, argv[0], argv[0] );
    return EXIT_FAILURE;
  }
  
  // validate .ano file
  char *retValue;
  retValue = strchr( outFilename, DOT_EXT );
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
  
  // generate the anagram file
  errno = 0;
  int numAna = generateAnagramFile( inFilename, outFilename );
  if( errno != 0 ) {
    return EXIT_FAILURE;
  }
  // no errors
  fprintf( stdout, STR_ANAGRAM_FILE, outFilename, numAna ); 
  return EXIT_SUCCESS;
}
