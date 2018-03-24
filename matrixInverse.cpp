
/**********************************************************************************
 *  This program computes the inverse of a 5X5 matrix using the  LU Decomposition *
 *  mathod.                                                                       *
 *                                                                                *
 *  The input matrix is modified and holds the inverse of the original matrix     *
 *   at the end of the program. No other array is used in the implementation.     *
 *                                                                                *
 *  The time taken for computing the inverse is calculated and reported for each  *
 *  of the test cases.                                                            *
 *                                                                                *
 **********************************************************************************/

#include <iostream>
#include <stdio.h>
#include "timer.h"
#include <time.h>
#include <cstdlib>
#include <iomanip>
#include <sys/time.h>
#include "Kokkos_Core.hpp"

using namespace std;

/*Method to populate a matrix of 5 X 5 with random integers from the range [0,100) */
void fill_matrix(Kokkos::View<float[5][5]>& A) {
  const int LIMIT = 100;
  struct timeval Tv;
  gettimeofday(&Tv, NULL); 
  srand48(Tv.tv_usec); // using time of day as seed for the random number generation
  int val;
  for(int i=0; i<5; ++i) { 
    for(int j=0; j<5; ++j) {
      val = (int)(drand48() * LIMIT) ;
      A(i,j) = (double)val;
    }
  }
}

/*Method to display a 5 X 5 matrix*/

void print_matrix(Kokkos::View<float[5][5]>& A) {
  cout << setiosflags(ios::fixed) << setprecision(4);
  for(int i=0; i<5; ++i) {
    for(int j=0; j<5; ++j)
      cout << A(i,j) << "\t";
    cout << endl;
  }
}

void matrixInverse(Kokkos::View<float[5][5]>& A) {

  // Implementation by LU decomposition

  if(A(0,0) == 0) { // division by 0 error
    cerr << "Inverse does not exist" << endl;  
    exit(1);
  }
  for (int i = 1; i < 5; ++i) {
    A(0,i) /= A(0,0);
  }

  for (int i = 1; i < 5; ++i) {
    for (int j = i; j < 5; ++j) {
      float sum = 0.0;
      for (int k = 0; k < i; ++k) {
        sum += A(j,k) * A(k,i);
      }
      A(j,i) -= sum;
    }
    if (i == 4) continue;

    float divi = A(i,i);
    if(divi == 0) { 
      cerr << "Inverse does not exist" << endl;  
      exit(1);
    }

    for (int j=i+1; j < 5; ++j) {
      float sum = 0.0f;
      for (int k = 0; k < i; ++k)
        sum += A(i,k)*A(k,j);
      A(i,j) = (A(i,j)-sum) / divi;
    }
  }


  //
  // Invert L
  //
  for (int i = 0; i < 5; ++i ) {
    for ( int j = i; j < 5; ++j ) {
      float divj = A(j,j);
      if(divj == 0) {
        cerr << "Inverse does not exist" << endl;  
        exit(1);
      }
      float x = 1.0;
      if ( i != j ) {
        x = 0.0;
        for ( int k = i; k < j; ++k ) 
          x -= A(j,k)*A(k,i);
      }
      A(j,i) = x / divj; //A[j][j];
    }
  }

  //
  // Invert U
  //
  for (int i = 0; i < 5; ++i ) {
    for (int j = i+1; j < 5; ++j ) {
      if ( i == j ) continue;
      float sum = 0.0;
      for ( int k = i; k < j; ++k ) 
        sum += A(k,j)*( (i==k) ? 1.0f : A(i,k) );
      A(i,j) = -sum;
    }
  }

  //
  // Final Inversion
  //
  //
  for (int i = 0; i < 5; ++i ) {
    for ( int j = 0; j < 5; ++j ) {
      float sum = 0.0;
      int init = (i>j)? i:j;
      for (int k = init; k < 5; ++k )  
        sum += ((j==k) ? 1.0f : A(j,k))*A(k,i);
      A(j,i) = sum;
    }
  }
}

int main(int argc, char* argv[]) {

  Kokkos::initialize(argc, argv);
  Kokkos::View<float[5][5]> A("A"); // declaring an array of floats having dimensions 5 X 5.

  // Testcases with predefined matrices
  /*******************
    1.  * Input matrix:
    53 15  52  93  26  
    71 62  28  59  66  
    37 60  46  44  34  
    78 49  9   11  25  
    12 94  22  62  58
   **************************
   * Inverse of the matrix:

   0.00370502   -0.000212067  -0.00450282   0.0133281  -0.00452485 
   -0.000196692  -0.0191792     0.00217756   0.0143345   0.0144577 
   -0.00732044    0.0056891     0.0387887   -0.0156529  -0.0191835  
   0.0172788    -0.0115036    -0.0208713    0.00634738  0.0148436 
   -0.0161415     0.0412664     0.00500024  -0.0268371  -0.0138446   
   ****************************************************************/

  // creating the original matrix by populating A
  A(0,0) = 53; A(0,1) = 15; A(0,2) = 52; A(0,3) = 93; A(0,4) = 26;
  A(1,0) = 71; A(1,1) = 62; A(1,2) = 28; A(1,3) = 59; A(1,4) = 66;
  A(2,0) = 37; A(2,1) = 60; A(2,2) = 46; A(2,3) = 44; A(2,4) = 34;
  A(3,0) = 78; A(3,1) = 49; A(3,2) = 9;  A(3,3) = 11; A(3,4) = 25;
  A(4,0) = 12; A(4,1) = 94; A(4,2) = 22; A(4,3) = 62; A(4,4) = 58;
  cout << endl << "Predefined testcase -1:" << endl << endl;
  cout << "Input matrix:" << endl;
  print_matrix(A);
  CPUTimer cputimer; //from timer.h
  cputimer.Start(); // start timer
  matrixInverse(A);
  cputimer.Stop(); // stop timer
  cout << endl;
  cout << "Inverse of the matrix" << endl << endl;
  print_matrix(A);
  cout << endl;
  printf("time taken to compute the inverse = %.6g (sec)\n", cputimer.Elapsed());
  cout << "---------------------------XX-----------------------" << endl << endl;

  /*******************
    2.* Input matrix:
    2   3   6   7   11
    8   4   9   5   10
    13  12  14  15  16
    17  18  19  20  21
    22  23  24  25  26
   **************************
   * Inverse of the matrix:

   0.5   -0.1667   0.5         -6.3     4.6333
   0.5   -0.1667  -0.5         -4.3     3.6333
   -1.5    0.6111  -0.5         14.233  -10.789
   -0.5   -0.0555   0.5         4.4333  -3.6556
   1     -0.2222  -3.041e-06  -8.2668   6.3778
   ****************************************************************/

  // creating the original matrix by populating A
  A(0,0) = 2 ; A(0,1) = 3 ; A(0,2) = 6 ; A(0,3) = 7 ; A(0,4) = 11;
  A(1,0) = 8 ; A(1,1) = 4 ; A(1,2) = 9 ; A(1,3) = 5 ; A(1,4) = 10;
  A(2,0) = 13; A(2,1) = 12; A(2,2) = 14; A(2,3) = 15; A(2,4) = 16;
  A(3,0) = 17; A(3,1) = 18; A(3,2) = 19; A(3,3) = 20; A(3,4) = 21;
  A(4,0) = 22; A(4,1) = 23; A(4,2) = 24; A(4,3) = 25; A(4,4) = 26;
  cout << endl << "Predefined testcase - 2:" << endl << endl;
  cout << "Input matrix:" << endl;
  print_matrix(A);
  CPUTimer cputimer1; //from timer.h
  cputimer1.Start(); // start timer
  matrixInverse(A);
  cputimer1.Stop(); // stop timer
  cout << endl;
  cout << "Inverse of the matrix" << endl << endl;
  print_matrix(A);
  cout << endl;
  printf("time taken to compute the inverse = %.6g (sec)\n", cputimer.Elapsed());
  cout << "---------------------------XX-----------------------" << endl << endl;


  cout << "Randomly generated test cases: " << endl;
  // creating 5 testcases with matrices populated with random integers in the range [0,100)
  for(int testcase = 1; testcase <= 5; ++testcase) {
    cout << "Testcase-" << testcase  << ":"<< endl << endl;
    fill_matrix(A);
    cout << "Input matrix:" << endl;
    print_matrix(A);

    CPUTimer cputimer; //from timer.h

    cputimer.Start(); // start timer

    matrixInverse(A); // finding the inverse of the matrix A

    cputimer.Stop(); // stop timer

    // printing the inverse 

    cout << endl;
    cout << "Inverse of the matrix" << endl << endl;
    print_matrix(A);
    cout << endl;

    printf("time taken to compute the inverse = %.6g (sec)\n", cputimer.Elapsed());
    cout << "---------------------------XX-----------------------" << endl << endl;
  }
  //  populate the matrix
  Kokkos::finalize();
  return 0;
}
