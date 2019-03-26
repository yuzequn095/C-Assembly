#ifndef PAMT1_H   /* Macro Guard */
#define PAMT1_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

#include <omp.h>  // For OpenMP directives

/*
 * Used in init.c and omp_init.c
 */

#define BIT_7 0x80
#define BIT_0 0x01
#define BITS_IN_A_BYTE 8
#define BITS_IN_A_NIBBLE 4
#define UPPER_NIBBLE 0xF0

/*
 * Local function prototypes for PAMT1
 */

void init( unsigned char a[],
           size_t arraySize,
           unsigned char data[],
           size_t dataSize );

void omp_init( unsigned char a[],
               size_t arraySize,
               unsigned char data[],
               size_t dataSize );


struct result1 function1( unsigned char a[],
                          size_t arraySize );

struct result1 omp_function1( unsigned char a[],
                              size_t arraySize );

struct result2 function2( unsigned char a[],
                          size_t arraySize );

struct result2 omp_function2( unsigned char a[],
                              size_t arraySize );

void usage( char *filename,
            size_t dataSize );

/*
 * If you want to see what size_t is typdef'ed to be:
 *
 *   echo '#include <stdlib.h>' | cpp | egrep 'typedef .* size_t'
 */

/*
 * The data structure to encapsulate the results of the calculations.
 */

struct result1 {
  unsigned int min;
  unsigned int max;
  unsigned long long int sum;
};

struct result2 {
  unsigned int min;
  unsigned int max;
  double sum;
};

#endif  /* PAMT1_H */

