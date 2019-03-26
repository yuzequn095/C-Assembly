/*
 * Filename: function1.c
 * Author: Zequn YU
 * Userid: cs30xga
 * Description: Finds the minimum and maximum value in the array and
 *              sums the square of each element in array a[].
 *              (Sequential version)
 * Date: Feb 22th, 2019
 * Sources of Help: Write-up
 */

/*
 * See pamt1.h for definition of struct result1
 */

#include "pamt1.h"

/*
 * Function name: function1()
 *
 * Function prototype: struct result1 function1( unsigned char a[],
 *                                               size_t arraySize );
 *
 * Description: squares each element (a[i] * a[i]) and adds this to an
 *              accumulating sum. Find the min and max values in the array.
 *
 * Parameters: a[]        array to perform sum of squares, min, and max 
 *             arraySize  size of the array
 *
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: A struct result1 populated with the sum of the squares
 *               of each element, overall min and max values.
 */

struct result1 function1( unsigned char a[], size_t size ) {
  struct result1 result;
  

/*
 *  Fill in the body of this function.
 */
  
  //local vars
  unsigned long long int sum = a[0]*a[0];
  unsigned int min = a[0];
  unsigned int max = a[0];

  //iterator
  for( size_t i = 1; i < size; i++ ) {
    sum = a[i]*a[i] + sum;
    
    //update
    if( a[i] < min ) {
      min  = a[i];
    }
    if( a[i] > max ) {
      max = a[i];
    }
  }
  
  //set 
  result.sum = sum;
  result.min = min;
  result.max = max;

  return result; // return the struct by value
}
