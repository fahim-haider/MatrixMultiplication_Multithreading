#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include <random>
#include <filesystem>
#include <chrono>
#include <windows.h>

using namespace std;

// Stores the one dimensional size of the matrix
const int MATRIXLENGTH = 1000;
// Creates matrices of MATRIXLENGTH in length and width!
// Thus, the dimensions of the matrix is MATRIXLENGTH x MATRIXLENGTH
int matrix1[MATRIXLENGTH][MATRIXLENGTH];
int matrix2[MATRIXLENGTH][MATRIXLENGTH];
int result[MATRIXLENGTH][MATRIXLENGTH];

// Semaphore variable!
HANDLE productLock;

// Create a random number generator with an upper and lower bound! (inclusive)
int randomNumberGenerator(int lower_bound, int upper_bound) {
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> distr(lower_bound, upper_bound);

    return distr(gen);
}

void fillMatrices() {
    // Fill up the matrices!
    for (int i = 0; i < MATRIXLENGTH; i++) {
        for (int j = 0; j < MATRIXLENGTH; j++) {
            matrix1[i][j] = randomNumberGenerator(0, 99);
            matrix2[i][j] = randomNumberGenerator(0, 99);
        }
    }
}

// Calculate multiplicative product of the two matrices: matrix1 and matrix2
int calculateProduct() {
    // Loop through rows
    for(int i = 0; i < MATRIXLENGTH; i++) {
        // Loop through columns
        for(int j = 0; j < MATRIXLENGTH; j++) {
            long temp = 0;
            // Loop through elements of current row and column combination
            for(int index = 0; index < MATRIXLENGTH; index++) {
                temp += matrix1[i][index] * matrix2[index][j];
            }
            //WaitForSingleObject(productLock, INFINITE);
            result[i][j] += temp;
            //ReleaseSemaphore(productLock, 1, nullptr);
        }
    }
    return 0;
}

int main (int argc, char* argv[]) {
    //Creates output file
    ofstream outFile("Results.txt");

    productLock = CreateSemaphore(nullptr, 1, 1, nullptr);

    if(productLock == nullptr) {
        cerr << "CreateSemaphore error!" << GetLastError() << endl;
        return 1;
    }

    auto startFill = chrono::high_resolution_clock::now();
    fillMatrices();
    auto endFill = chrono::high_resolution_clock::now();

    chrono::duration<double> durationFill = endFill - startFill;

    auto startCalc = chrono::high_resolution_clock::now();
    calculateProduct();
    auto endCalc = chrono::high_resolution_clock::now();

    chrono::duration<double> durationCalc = endCalc - startCalc;

    outFile << "Matrix size:                        " << 
    MATRIXLENGTH << " x " << MATRIXLENGTH << endl;
    outFile << "Result[0][0]:                       " << 
    result[0][0] << endl;
    outFile << "Time elapsed to fill matrices:      " << 
    durationFill.count() << endl;
    outFile << "Time elapsed to calculate product:  " << 
    durationCalc.count() << endl;
}