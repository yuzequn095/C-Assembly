/*
 * Filename: main.c
 * Author: Zequn Yu
 * Userid: cs30xga
 * Description: Drive the program
 * Date: Feb 22th, 2019
 * Sources of Help: None
 */

#include <errno.h>

#include "pamt1.h"

#define BASE 10

/*
 * Function name: main()
 * Function prototype: int main( int argc, char *argv[] );
 * Description: Drive the rest program.
 * Parameters: argc - number of parameter
 *             argv - parameter
 * Side Effects: Print output to stdout or stderr.
 * Error Conditions: None.
 * Return Value: 0 indicating successful execution.
 */

int main( int argc, char *argv[] ) {

  unsigned char data[] = { 0x41, 0x59, 0x47, 0x3F, 0x3C, 0x24,
                           0x3C, 0x3F, 0x47, 0x59, 0x41 };
  size_t dataSize = sizeof(data);

  char *expectedStr = "CSE30 03ESC";

  if ( argc != 2 ) {
    usage(argv[0], dataSize);
    exit( -1 );
  }

  struct result1 result1;
  struct result2 result2;
  double startTime, endTime;
  double seqTime, parTime;

  /* Convert command-line arg to an unsigned long and initialize array */
  char *endptr;

  errno = 0;
  size_t arraySize = strtoul( argv[1], &endptr, BASE );

  if ( errno != 0 || *endptr != '\0' ||
       arraySize < dataSize || arraySize > UINT_MAX ) {
    usage(argv[0], dataSize);
    exit( -1 );
  }

  unsigned char *array = (unsigned char *) malloc( arraySize );

  if ( array == NULL ) {
     perror( "array is NULL" );
     (void) fprintf( stderr, 
            "Probably due to array_size too large for this system.\n" );
     exit( 1 );
  }

  (void) printf( "Using array size = %zu\n", arraySize );

  /* First do sequential init */

  (void) printf( "Initializing array with values using " );
  (void) printf( "sequential init()\n  [be patient with large values]\n" );

  startTime = omp_get_wtime();
  init( array, arraySize, data, dataSize );
  endTime = omp_get_wtime();

  (void) printf( "\nChecking that sequential init produced " );
  (void) printf( "the values as expected\n" );
  (void) printf( "Checking the first %zu bytes only\n", dataSize );
  (void) printf( "Should print out the string: \"%s\"\n", expectedStr );

  int error = 0;

  for ( int i = 0; i < dataSize; i++ ) {
    (void) printf( "%c", array[i] );

    if ( array[i] != expectedStr[i] ) {
      error = 1;
      break;
    }
  }

  if ( error ) {
    (void) printf( "\nYour init.c doesn't seem to be correct!\n" );
    (void) printf( "Exiting ...\n" );
    exit( 1 );
  }

  (void) printf( "\n\n" );

  seqTime = endTime - startTime;
  (void) printf( "Sequential init time = %f\n\n", seqTime );

  /*
   * After init (sequential).
   *        Comment out the return 0; below to continue to the next
   *       phase involving parallelizing omp_init.c
   */

  //return 0;



  /* Next do parallel omp_init using OpenMP directives */

  (void) printf( "Initializing array with same values using parallel " );
  (void) printf( "omp_init()\n  [be less patient with large values]\n" );

  /* Print number of threads on this system. Just thread #0 prints vs. all. */
  #pragma omp parallel
  {
    if ( omp_get_thread_num() == 0 ) {
      (void) printf( "\nNum of threads = %d\n", omp_get_num_threads() );
    }
  }

  for ( int i = 0; i < dataSize; i++ ) {
    array[i] = 'X';
  }

  startTime = omp_get_wtime();
  omp_init( array, arraySize, data, dataSize );
  endTime = omp_get_wtime();

  (void) printf( "\nChecking that parallel omp_init produced " );
  (void) printf( "the values as expected\n" );
  (void) printf( "Checking the first %zu bytes only\n", dataSize );
  (void) printf( "Should print out the string: \"%s\"\n", expectedStr );

  for ( int i = 0; i < dataSize; i++ ) {
    (void) printf( "%c", array[i] );

    if ( array[i] != expectedStr[i] ) {
      error = 1;
      break;
    }
  }

  if ( error ) {
    (void) printf( "\nYour parallel omp_init.c doesn't seem to be correct!\n" );
    (void) printf( "Exiting ...\n" );
    exit( 1 );
  }

  (void) printf( "\n\n" );

  parTime = endTime - startTime;
  (void) printf( "Parallel omp_init time = %f\n\n", parTime );

  (void) printf( "*** parallel omp_init Speed-up: %f ***\n\n",
                 seqTime / parTime );


  /*
   * After omp_init (parallel).
   *  Comment out the return 0; below to continue to the next
   *       phase involving sequential function1.c
   */

  //return 0;


  /* First do sequential function1 */

  (void) printf( "\nSequential function1 [be patient]\n" );  

  startTime = omp_get_wtime();
  result1 = function1( array, arraySize );
  endTime = omp_get_wtime();

  seqTime = endTime - startTime;
  (void) printf( "Sequential function1 time = %f\n\n", seqTime );

  (void) printf( "Min value is: %d\n", result1.min );
  (void) printf( "Max value is: %d\n", result1.max );
  (void) printf( "Squared Sum is: %llu\n", result1.sum );
  (void) printf( "Completed in %f sec\n\n", seqTime );

  /*
   * After function1 (sequential).
   *  Comment out the return 0; below to continue to the next
   *       phase involving parallel omp_function1.c
   */

  //return 0;


  /* Now do parallel function1 using OpenMP directives */

  (void) printf( "Parallel omp_function1 [don't need to be as patient]\n" );  

  startTime = omp_get_wtime();
  result1 = omp_function1( array, arraySize );
  endTime = omp_get_wtime();

  parTime = endTime - startTime;
  (void) printf( "Parallel omp_function1 time = %f\n\n", parTime );

  (void) printf( "Min value is: %d\n", result1.min );
  (void) printf( "Max value is: %d\n", result1.max );
  (void) printf( "Squared Sum is: %llu\n", result1.sum );
  (void) printf( "Completed in %f sec\n\n", parTime );

  (void) printf( "*** parallel omp_function1 Speed-up: %f ***\n\n",
                 seqTime / parTime );

  /*
   * After omp_function1 (parallel).
   *  Comment out the return 0; below to continue to the next
   *       phase involving sequential function2.c
   */

  //return 0;


  /* First do sequential function2 */

  (void) printf( "\nSequential function2 [be patient]\n" );  

  startTime = omp_get_wtime();
  result2 = function2( array, arraySize );
  endTime = omp_get_wtime();

  seqTime = endTime - startTime;
  (void) printf( "Sequential function2 time = %f\n\n", seqTime );

  (void) printf( "Min value is: %d\n", result2.min );
  (void) printf( "Max value is: %d\n", result2.max );
  (void) printf( "Sqrt Sum is: %f\n", result2.sum );
  (void) printf( "Completed in %f sec\n\n", seqTime );

  /*
   * After function2 (sequential).
   *  Comment out the return 0; below to continue to the next
   *       phase involving parallel omp_function2.c
   */

  //return 0;


  /* Now do parallel omp_function2 using OpenMP directives */

  (void) printf( "Parallel omp_function2 [don't need to be as patient]\n" );  

  startTime = omp_get_wtime();
  result2 = omp_function2( array, arraySize );
  endTime = omp_get_wtime();

  parTime = endTime - startTime;
  (void) printf( "Parallel omp_funciton2 time = %f\n\n", parTime );

  (void) printf( "Min value is: %d\n", result2.min );
  (void) printf( "Max value is: %d\n", result2.max );
  (void) printf( "Sqrt Sum is: %f\n", result2.sum );
  (void) printf( "Completed in %f sec\n\n", parTime );

  (void) printf( "*** parallel omp_function2 Speed-up: %f ***\n\n",
                 seqTime / parTime );


  /* Free up dynamically allocated memory on the Heap. */

  free(array);

  return 0;
}

/*
 * Function name: usage()
 * Function prototype: void usage( char *filename, size_t dataSize )
 * Description: Prints a brief usage message to stderr
 * Parameters: filename   name of this program, to be printed out in message
 *             dataSize   size of the data[] array
 * Side Effects: Prints usage message to stderr
 * Error Conditions: None.
 */

void usage( char *filename, size_t dataSize ) {
  (void) fprintf( stderr, "\nUsage: %s array_size\n", filename );
  (void) fprintf( stderr, "   array_size  (must be >= %zu and <= %u)\n\n",
                          dataSize, UINT_MAX );
}

