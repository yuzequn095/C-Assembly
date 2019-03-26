/*
 * Filename: loadQueryTable.C
 * Author: Zequn Yu
 * Userid: cs30xga
 * Date: Feb 17th, 2019
 * Source of Help: http://c.biancheng.net/cpp/html/326.html
 *                 https://blog.udemy.com/fread-c/
 */

#include <stdio.h>
#include <stdlib.h>
#include "pa3.h"
#include "pa3Strings.h"
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>


/*
 * Function Name: loadQueryTable()
 * Funtion Prototype: int loadQueryTable( const char * anagramFilename,
 *                      queryTable_t * queryTable);
 *
 * Description: This funtion will read one anagram at a time from the anagram
 *              file and set up a queryTable.
 * Side Effects: It may output error information to stderr
 * Error Conditions: error opening anagramFilename; anagram file doesn't 
 *                   have size; insertIntoBucket fails.
 * Return Value: -1 if any error occured, 0 otherwise.
 */

int loadQueryTable( const char * anagramFilename, queryTable_t * queryTable ){

  // open anagramFilename using mode 'rb'
  errno = 0;
  FILE *ifstream;
  ifstream = fopen( anagramFilename, "rb" );
  if( errno == EACCES ){
    fprintf( stderr, STR_ERR_IN_FILE_PERMISSION, anagramFilename );
    return -1;
  }
  if( errno == ENOENT ){
    fprintf( stderr, STR_ERR_IN_FILE_INVALID, anagramFilename );
    return -1;
  }
  
  // check size of file
  // if file size is not divisibly by the size of a single anagram
  // close the input file and print error
  struct stat buf;
  stat(anagramFilename, &buf);
  if( (buf.st_size % sizeof(anagram_t)) != 0 ){
    fclose(ifstream);
    fprintf( stderr, STR_ERR_ANAGRAM_FILE_CORRUPT, anagramFilename );
    return -1;
  }

  // read in one anagram at a time using fread
  // use getBucketIndex to get index
  // use insertIntoBucket to insert (if fail then print error info)
  anagram_t record; 
  if( ifstream != NULL ) {
    while( !feof(ifstream) ) {
      fread( &record, sizeof(record), 1, ifstream );
      int idx = getBucketIndex( record.hashcode, queryTable->size );
      int err = insertIntoBucket( &(queryTable->tablePtr[idx]), &record );
      // check errors
      if( err == -1 ) {
        fprintf( stderr, STR_ERR_INSERT );
        fclose( ifstream );
        return -1;
      }
    }
  }

  // after reading then sort
  qsort( queryTable->tablePtr, queryTable->size,
         sizeof(queryTable->tablePtr[0]),  anagramCmp );
  
  // close file
  fclose( ifstream );
  return 0;
  
}
