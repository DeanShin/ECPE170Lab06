// Adapted from https://gustavus.edu/+max/courses/F2011/MCS-284/labs/lab3/
// Max Hailperin, Gustavus Adolphus College

// This program measures the speed of the matrix computation C = C + A * B,
// which is a slight generalization of matrix multiplication.  (If C is
// initially 0, then this would be matrix multiplication.)  The three
// matrices A, B, and C are all of size n*n, where n is passed to this
// program on its command line.  The reported result is the number of
// double-precision (64-bit) floating point operations per second.
// The operational speed is unlikely to be significantly influenced
// by the particular numbers being multiplied and added; the matrices are
// initialized to a specific pseudo-random sequence for repeatability.

#include <stdlib.h>
#include <assert.h>
#include <sys/resource.h>
#include <stdio.h>

#include "matrix_math.h"

// Generate a pseudo-random double-precision floating point number
double randomDouble()
{
  return random() / (double) 0x7fffffff;
}

int main(int argc, char* argv[])
{
  int n, i;
  int algorithm;

  if(argc != 3)
    {
      printf("Program usage: %s <algorithm #> <maxtrix-dimension>\n", argv[0]);
      return 1;
    }

  algorithm = atoi(argv[1]);
  n = atoi(argv[2]);

  if(algorithm < 1 || algorithm > 2)
    {
      printf("Error: Algorithm must be 1 or 2\n");
      return 1;
    }

  if(n << 24 >> 24 != 0)
    {
      printf("Error: Maxtrix dimension must be divisible by 256\n");
      return 1;
    }

  printf("Configuration: Algorithm %i, array size %i\n", algorithm, n);

  // Allocate memory for three n*n arrays of 
  // double-precision floating point numbers.

  // Note on matrix storage in memory:
  // Each matrix is stored as a sequence of n^2 values. The first n 
  // constitute the first row of the matrix, the next n the second row, etc.
  // (This is called "row major order".) As such, given that we are numbering the
  // rows and columns starting from 0, to reach a position that is in row
  // number i requires skipping over i full rows of n elements.
  // Thus, array[row][column] is the same as array[row*n+column]

  printf("Total size of all 3 arrays: %.2g MB\n", 3*sizeof(double)*n*n/1024.0/1024.0);

  double *a = malloc(n*n*sizeof(double));
  assert(a != NULL);
  double *b = malloc(n*n*sizeof(double));
  assert(b != NULL);
  double *c = malloc(n*n*sizeof(double));
  assert(c != NULL);

  // Reset the pseudo-random number generator to a known value 
  // so experiments are *repeatable*
  srandom(284); 

  // Initialize the arrays with a fixed sequence of pseudo-random numbers.
  for(i = 0; i < n*n; i++)
    {
      a[i] = randomDouble();
      b[i] = randomDouble();
      c[i] = randomDouble();
    }

  // Get resource consumption information before the matrix 
  // computation as a baseline.
  struct rusage before;
  assert(getrusage(RUSAGE_SELF, &before) == 0);

  // Now comes the matrix computation itself
  if(algorithm == 1)
     multiply_1(a, b, c, n);
  else if(algorithm == 2)
    multiply_2(a, b, c, n);

  // Get the resource consumption information after the matrix computation.
  struct rusage after;
  assert(getrusage(RUSAGE_SELF, &after) == 0);

  printf("Result for sanity checking: c[%i][%i]=%g\n",
	 n-1, n-1, c[n*n-1]);

  // Print the number of floating point operations per second.
  // This is calculated based on the total user-mode CPU time elapsed and
  // the fact that 2*n*n*n floating point operations are performed (one
  // floating point multiplication and one floating point addition each
  // of the n*n*n times that the line marked above is executed).
  printf("Floating-point ops/sec: %.2E\n",
	 2.0 * n * n * n /
	 (((after.ru_utime.tv_usec - before.ru_utime.tv_usec) * 1e-6) +
	  (after.ru_utime.tv_sec - before.ru_utime.tv_sec)));


  // Exit normally.
  return 0;
}

// Matrix multiply:  C = C + A*B
// Algorithm 1
void multiply_1(double *a, double*b, double *c, int n)
{
  int i, j, k;
  for(i = 0; i < n; i++){
    for(j = 0; j < n; j++){
      for(k = 0; k < n; k++){
	c[i*n + j] += a[i*n + k] * b[k*n + j]; // <- this line is executed n*n*n times
      }
    }
  }
}

// Matrix multiply:  C = C + A*B
// Algorithm 2
void multiply_2(double *a, double*b, double *c, int n)
{
  int i, j, k;

  // OPTIMIZATION 1: Swapping order of loops to operate on adjacent elements
  for(i = 0; i < n; i++){
    for(k = 0; k < n; k++){
      for(j = 0; j < n; j++){
	c[i*n + j] += a[i*n + k] * b[k*n + j]; // <- this line is executed n*n*n times
      }
    }
  }
}
