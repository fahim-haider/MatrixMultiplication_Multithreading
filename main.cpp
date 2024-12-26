#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include <random>
#include <filesystem>
#include <chrono>
#include <windows.h>
#include "main.hpp"
#include "MTMode.hpp"
#include "SimpleMode.hpp"

using namespace std;

// Creates matrices of MATRIXLENGTH in length and width!
// Thus, the dimensions of the matrix is MATRIXLENGTH x MATRIXLENGTH
int matrix1[MATRIXLENGTH][MATRIXLENGTH];
int matrix2[MATRIXLENGTH][MATRIXLENGTH];
int result[MATRIXLENGTH][MATRIXLENGTH];

// Semaphore variable!
HANDLE productLock;

// Global output file that all src files can use to write results to
ofstream outFile;

// Create a random number generator with an upper and lower bound! (inclusive)
int randomNumberGenerator(int lower_bound, int upper_bound) {
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> distr(lower_bound, upper_bound);

    return distr(gen);
}

void fillMatrices(int threadID) {
    // Fill up the matrices!
    for (int i = 0; i < MATRIXLENGTH; i++) {
        if(threadID < 0) {
            for (int j = 0; j < MATRIXLENGTH; j++) {
                matrix1[i][j] = randomNumberGenerator(0, 999);
                matrix2[i][j] = randomNumberGenerator(0, 999);
            }
        }
        else {
            for (int j = threadID; j < MATRIXLENGTH; j += THREADCOUNT) {
                matrix1[i][j] = randomNumberGenerator(0, 999);
                matrix2[i][j] = randomNumberGenerator(0, 999);
            }
        }
    }
}

int main (int argc, char* argv[]) {
    //Creates output file
    outFile.open("Results.txt");

    productLock = CreateSemaphore(nullptr, 1, 1, nullptr);

    if(productLock == nullptr) {
        cerr << "CreateSemaphore error!" << GetLastError() << endl;
        return 1;
    }

    SimpleMode();
    MTMode();

    outFile.close();
}