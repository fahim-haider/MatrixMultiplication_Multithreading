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

long dotProduct = 0;
const int THREADCOUNT = 4;

// Create a random number generator with an upper and lower bound! (inclusive)
int randomNumberGenerator(int lower_bound, int upper_bound) {
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> distr(lower_bound, upper_bound);

    return distr(gen);
}

void fillMatrices(int threadID) {
    // Fill up the matrices!
    for (int i = threadID; i < MATRIXLENGTH; i += THREADCOUNT) {
        for (int j = threadID; j < MATRIXLENGTH; j += THREADCOUNT) {
            matrix1[i][j] = randomNumberGenerator(0, 99);
            matrix2[i][j] = randomNumberGenerator(0, 99);
        }
    }
}

int calculateProduct() {
    // For every row of m1, multiple its constituents with the corresponding column of m2
    // Loop through rows
    for(int i = 0; i < MATRIXLENGTH; i++) {
        // Loop through elements of row
        for(int j = 0; j < MATRIXLENGTH; j++) {
            dotProduct += matrix1[i][j] * matrix2[j][i];
        }
    }
    return 0;
}

HANDLE productLock;
int main (int argc, char* argv[]) {
    //Creates output file
    ofstream outFile("Results.txt");

    productLock = CreateSemaphore(nullptr, 1, 1, nullptr);

    if(productLock == nullptr) {
        cerr << "CreateSemaphore error!" << GetLastError() << endl;
        return 1;
    }

    thread threads[THREADCOUNT];

    auto startFill = chrono::high_resolution_clock::now();
    for(int i = 0; i < THREADCOUNT; i ++) {
        threads[i] = thread(fillMatrices, i);
    }

    for(auto& th: threads) {
        th.join();
    }

    auto endFill = chrono::high_resolution_clock::now();

    chrono::duration<double> durationFill = endFill - startFill;

    auto startCalc = chrono::high_resolution_clock::now();
    calculateProduct();
    auto endCalc = chrono::high_resolution_clock::now();

    chrono::duration<double> durationCalc = endCalc - startCalc;

    outFile << "Matrix size:                        " << MATRIXLENGTH << " x " << MATRIXLENGTH << endl;
    outFile << "Dot Product:                        " << dotProduct << endl;
    outFile << "Time elapsed to fill matrices:      " << durationFill.count() << endl;
    outFile << "Time elapsed to calculate product:  " << durationCalc.count() << endl;
}