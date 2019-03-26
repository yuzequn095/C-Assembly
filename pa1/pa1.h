/*
 * Filename: pa1.h
 * Author: Zequn Yu
 * UserId: cs30xga
 * Date: 1/17/2019
 * Sources of Help: None.
 */

#ifndef PA1_H
#define PA1_H


// Arg constants.
#define MIN_NUM_ARGS 2
#define MAX_NUM_ARGS 4

// argv[] indices.
#define PROG_NAME_IDX 0
#define SIZE_IDX 1
#define UPWARD_CHAR_IDX 2
#define DOWNWARD_CHAR_IDX 3

// Math constants.
#define HALF_DIVISOR 2
#define EVEN_DIVISOR 2
#define DOUBLE_FACTOR 2

#define BASE 0

// Pinwheel constants.
#define MIN_SIZE 4
#define MAX_SIZE 50

#define DEFAULT_UPWARD_CHAR '@'
#define DEFAULT_DOWNWARD_CHAR '-'
#define SPACE_CHAR ' '
#define NEWLINE_CHAR '\n'

#define CHAR_ASCII_MIN 32
#define CHAR_ASCII_MAX 126

// Function prototypes.
int getRemainder( int dividend, int divisor );
int isDivisibleBy( int num, int divisor );
int isInBounds( int value, int minBound, int maxBound );
void printChar( char c );
void drawRadioactivePinwheel( int size, char upwardTriChar,
                              char downwardTriChar );

// EC function prototypes.
int getLargestDigit( int num, int base );


#endif /* PA1_H */
