/* 
 * Filename: pa2.h
 * Author: Zequn Yu
 * UserId: cs30xga
 * Date: Feb 13th, 2019
 * Sources of Help: Given.
 */

#ifndef PA2_H
#define PA2_H

#include <stdio.h>

/*
 * Constants
 */
#define EXPECTED_ARGS 4

/* Argument ranges/values */
#define MIN_PASSPHRASE_SIZE 4
#define MAX_PASSPHRASE_SIZE 8
#define KEY_SIZE 8
#define KEY_NUM 2
#define MASK_SIZE 8

/* Argument parsing */
#define DEF_BASE 0

/* Argument indices */
#define PASSPHRASE_INDEX 1
#define KEY_ONE_INDEX 2
#define KEY_TWO_INDEX 3 
#define ROTATE_VALUE_INDEX 4

/* Initialize each byte of passphrase with a recognizable value for debugging */
#define INIT_PASSPHRASE 0xA5

/* Argument range/values */
#define MIN_ROTATE 0
#define MAX_ROTATE 63

/* Return values for indicating errors */
#define ENDPTR_ERR -1
#define ERANGE_ERR -2
#define BOUND_ERR -3
#define LENGTH_ERR -4

/* Cipher constants */
#define CIPHER_BUFFER_SIZE 1024

/* Function prototypes for C routines */
int processKey( char * str, unsigned char key[] ); 
int processPassphrase( char * str, unsigned char * passphrase ); 

/* Function prototypes for Assembly routines */
void cipher( FILE * inFile, unsigned char mask[], int rotateValue );
void generateMask( unsigned char keys[], unsigned char passphrase[],
                   unsigned char mask[] );
int isInBounds( int value, int minBound, int maxBound );
int isOdd( int num );
int processRotateValue( char * str, int * rotateValue );
void rotate( unsigned char mask[], int rotateValue );
void xorBytes( unsigned char originalText[], unsigned char mask[],
               unsigned char cipherText[], unsigned int numBytes );
#endif /* PA2_H */
