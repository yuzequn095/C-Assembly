/* Filename: omp_function1.c
 * Author: Zequn Yu
 * Userid: cs30xga
 * Description: Use OpenMp to run calculations.
 * Date: Mar 6th, 2019
 */

/*
 * Function name: omp_function1()
 *
 * Function prototype: long long omp_function1( long long n,
 *                                              long long lo,
 *                                              long long hi );
 *
 * Params: n is the value we are checking to determine how many factors
 *           evenly divide into it.
 *         lo is the low (inclusive) range of possible factors to check.
 *         hi is the high (exclusive) range of possible factors to check.
 *
 * Algorithm:
 *   if n <= 1 return 0 (we won't deal with values less than 2). By definition,
 *       prime numbers are greater than 1.
 *
 *   if lo <= 1, set lo to 2 (we won't deal with factors less than 2).
 *
 *   set return value to 1 since n is evenly divisible by 1.
 *
 *   loop thru the range [lo, hi) as factors incrementing by 1 each time
 *       thru the loop checking if n is evenly divisible by each factor.
 *       If it is evenly divisible, increment the number of
 *       evenly-divisible factors for this range.
 *
 *   BE SURE TO DEFINE ALL LOCAL VARIABLES AS TYPE long long int
 *   
 *   There may be other more efficient algorithms, but this will do.
 *   We want to see how multi-threading in C with OpenMP
 *   might improve overall performance for this particular algorithm.
 *
 * Side Effects: None.
 *
 * Error Conditions: None.
 *
 * Return value: long long int indicating the number of evenly-divisible
 *               factors in n.
 */

long long omp_function1( long long n,
                         long long lo,
                         long long hi ) {

/*
 * Complete the omp_function1() code as specified above using
 *       OpenMP directives you learned about in pamt1.
 */
  // copy code from function1.c
  if( n <= 1 ) {
    return 0;
  }
  if( lo <= 1) {
    lo = 2;
  }
  long long int numFactor = 1;
  // OpenMP
  #pragma omp parallel for reduction (+:numFactor)
  for( long long int i = lo; i < hi; i++ ) {
    if( n % i == 0 ) {
      numFactor++;
    }
  }
  return numFactor;

}

