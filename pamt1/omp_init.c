/*
 * Filename: omp_init.c
 * Author: Zequn YU
 * Userid: cs30xga
 * Description: Initializes an array of bytes by applying a decoding
 *              algorithm specified below.
 *              (Parallel version)
 * Date: Feb 22th, 2019
 * Sources of Help: Write - up
 */

/*
 * Check pamt1.h for defines of BITS_IN_A_NIBBLE, BITS_IN_A_BYTE, BIT_7,
 * BIT_0, UPPER_NIBBLE
 */

#include "pamt1.h"

/*
 * Function name: omp_init()
 *
 * Function prototype:
 *      void omp_init( unsigned char a[], size_t arraySize,
 *                     unsigned char data[], size_t dataSize );
 *
 * Description: Initializes an array a[] of length size with decoded values
 *              from data[] using OpenMP directives to parallelize the
 *              process across multiple threads of execution.
 *
 * Parameters: a[]        array to be populated with decoded values
 *             arraySize  size of the array to be populated with decoded values
 *             data       array with original encoded values
 *             dataSize   size of the data array with encoded values
 *
 * Side Effects: After call to this function, the array a[] will contain
 *               decoded values from original data[] defined in main().
 *               The decoded values should be the same as those decoded in
 *               the sequential version.
 * Error Conditions: None.
 * Return Value: None.
 *
 *
 * Decoding algorithm:
 * 1) Define 4 unsigned char variables b1, b2, b3, b4;
 *
 * 2) For size_t i from zero thru all the elements in array a
 *   3a) Set a[i] to data[i modulus dataSize]
 *   3b) Set b4 to zero
 *
 *   3c) For int j from zero up to BITS_IN_A_NIBBLE (exclusive)
 *     4a) Set b1 to a[i] ANDed with (BIT_7 right shifted by j bits)
 *     4b) Set b1 to b1 right shifted by (BITS_IN_A BYTE - 1 - j bits)
 *     4c) Set b2 to a[i] ANDed with (BIT_0 left shifted by j bits)
 *     4d) Set b2 to b2 right shifted by j bits
 *     4e) Set b3 to b1 XORed with b2
 *     4f) Set b3 to b3 left shifted by j bits
 *     4g) Set b4 to b4 ORed with b3
 *
 *   3d) Set a[i] to (a[i] ANDed with UPPER_NIBBLE) ORed with b4
 *
 */

void omp_init( unsigned char a[], size_t arraySize,
               unsigned char data[], size_t dataSize ) {

/*
 * TODO: Fill in the body of this function.
 */
 //copy 
 unsigned char b1;
 unsigned char b2;
 unsigned char b3;
 unsigned char b4;

 #pragma omp parallel for private(b1, b2, b3, b4)
 for( size_t i = 0; i < arraySize; i++ ) {
   a[i] = data[i % dataSize];
   b4 = 0;
 
   //#pragma omp parallel for
   for( int j = 0; j < BITS_IN_A_NIBBLE; j++ ) {
     b1 = a[i] & (BIT_7 >> j );
     b1 = b1 >> (BITS_IN_A_BYTE - 1 -j);
     b2 = a[i] & (BIT_0 << j);
     b2 = b2 >> j;
     b3 = b1 ^ b2;
     b3 = b3 << j;
     b4 = b4 | b3;
   }
   a[i] = (a[i] & UPPER_NIBBLE) | b4;
 }
}

