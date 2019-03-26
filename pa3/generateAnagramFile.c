/*
 * Filename: generateAnagramFile.c
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Feb 27th, 2019
 * Source of Help: Di
 */
#include <stdio.h>
#include <stdlib.h>
#include"pa3.h"
#include "pa3Strings.h"
#include <string.h>
#include <ctype.h>
#include <errno.h>

#define NEW_LINE '\n'
#define NULL_TERM '\0'

/*
 * Function Name: generateAnagramFile()
 * Function prototype: int generateAnagramFile( const char *inFilename,
 *                     const char *outFilename );
 * Description: Read in one word at a time from words file, created an anagram
 *              struct for the word read in and then write anagram to anagram 
 *              file.
 * Parameters: inFilename - the name of input file
 *             outFilename - the name of output file
 * Side Effects: It may output information to stderr
 * Error Condition: Permission denied; invalid input filename; Error when 
 *                  output file; Error when writing
 * Return Value: -1 when error occureed, the number of anagrams when no errors.
 */

int generateAnagramFile( const char * inFilename, const char * outFilename ) {

  // open the input words file ( fopen ) ( mode 'r' )
  // set errno to 0
  // if errors print to stderr ( ENOENT EACCES )
  // permission denied: STR_ERR_IN_FILE_PERMISSION -> -1
  // doesn't exist: STR_ERR_IN_FILE_INVALID -> -1
  errno = 0;
  FILE *ifstream;
  ifstream = fopen( inFilename, "r" ); 
  // check errors
  if( errno == EACCES ) {
    fprintf( stderr, STR_ERR_IN_FILE_PERMISSION, inFilename );
    return -1;
  }
  if( errno == ENOENT ) {
    fprintf( stderr, STR_ERR_IN_FILE_INVALID, inFilename );
    return -1;
  }
  
  // open output file with "wb"
  // if error, print to stderr and clost input file
  errno = 0;
  FILE *ofstream;
  ofstream = fopen( outFilename, "wb" );
  if( errno != 0 ) {
    fprintf( stderr, STR_ERR_CREATE_ANAGRAM_FILE, outFilename );
    fclose( ifstream );
    return -1;
  }

  // make stack-allocated anagram_t
  anagram_t anagram;
  memset(&anagram, 0, sizeof(anagram_t));
  char BUFFER[MAX_WORD_SIZE];
  char *nl;
  // read in each word one time using fgets
  int countAna = 0;
  while( fgets( BUFFER, MAX_WORD_SIZE, ifstream ) != NULL ) {
    // replace new line char with null termination
    // if non-alphabetic then skip this word
    // assemble an anagram with assembleAnagram using word read in
    nl = strchr( BUFFER, NEW_LINE ); 
    // if new line?
    if( nl != NULL ) {
      *nl = NULL_TERM;
    }
    // if non-alphabetic?
    int flag = 0;
    for( int i = 0; i < strlen(BUFFER) - 1; i++ ) {
      if( isalpha(BUFFER[i]) == 0 ) {
        flag = 1;
        break;
      }
    }
    if ( flag != 0 ) {
      continue;
    }
    // assemble
    assembleAnagram( BUFFER, &anagram );
    countAna++;
    // write the anagram to output file
    errno = 0;
    fwrite( &anagram, sizeof(anagram_t), 1, ofstream );
    // check errors
    if( errno != 0 ) {
      fprintf( stderr, STR_ERR_WRITE_ANAGRAM, outFilename );
      fclose(ifstream);
      fclose(ofstream);
      return -1;
    }
  }

  return countAna;
}


