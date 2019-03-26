/*
 * Filename: function2.c
 * Author: Zequn Yu
 * Userid: cs30xga
 * Description: Finds the minimum and maximum value in the array and
 *              sums the square root of each element in array a[].
 *              (Sequential version)
 * Date: Feb 22th. 2019
 * Sources of Help: Write-up
 */

#include <math.h> // Needed for sqrt() function prototype

/*
 * See pamt1.h for definition of struct result2
 */

#include "pamt1.h"

/*
 * Function name: function2()
 *
 * Function prototype: struct result2 function2( unsigned char a[],
 *                                               size_t arraySize );
 *
 * Description: Gets the square root of each element (sqrt(a[i])) and adds
 *              this to an accumulating sum.
 *              Find the min and max values in the array.
 *
 * Parameters: a[]        array to perform square root, min, and max 
 *             arraySize  size of the array
 *
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: A struct result2 populated with the sum of the square roots
 *               of each element, overall min and max values.
 */

struct result2 function2( unsigned char a[], size_t size ) {
  struct result2 result;


/*
 *  Fill in the body of this function.
 */
  
  double sum = sqrt(a[0]);
  unsigned int min = a[0];
  unsigned int max = a[0];

  for( size_t i = 1; i < size; i++ ) {
    sum = sqrt(a[i]) + sum;

    if( a[i] < min ) {
      min = a[i];
    }

    if( a[i] > max ) {
      max = a[i];
    }
  }

  result.sum = sum;
  result.min = min;
  result.max = max;
  return result; // return the struct by value
}

