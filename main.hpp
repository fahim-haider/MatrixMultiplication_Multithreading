#ifndef MAIN_HPP
#define MAIN_HPP

#include <fstream>

using namespace std;

// Stores the one dimensional size of the matrix
const int MATRIXLENGTH = 1000;
// Stores the amount of threads to be used (if MT)
const int THREADCOUNT = 4;

// Semaphore variable!
extern HANDLE productLock;

// Creates matrices of MATRIXLENGTH in length and width!
// Thus, the dimensions of the matrix is MATRIXLENGTH x MATRIXLENGTH
extern int matrix1[MATRIXLENGTH][MATRIXLENGTH];
extern int matrix2[MATRIXLENGTH][MATRIXLENGTH];
extern int result[MATRIXLENGTH][MATRIXLENGTH];

extern ofstream outFile;

int randomNumberGenerator(int lower_bound, int upper_bound);
void fillMatrices(int threadID);


#endif