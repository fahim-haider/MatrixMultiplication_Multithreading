#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include <random>
#include <filesystem>
#include <chrono>
#include <windows.h>
#include "../include/MTTiling.hpp"
#include "../include/main.hpp"

using namespace std;

// Calculate multiplicative product of the two matrices: matrix1 and matrix2
int calculateProductMTTiling(int threadID) {
    // Loop through rows
    for(int ii = threadID*TILESIZE; ii < MATRIXLENGTH; ii+=TILESIZE*THREADCOUNT) {
        // Loop through columns
        for(int jj = 0; jj < MATRIXLENGTH; jj+= TILESIZE) {
            for(int kk = 0; kk < MATRIXLENGTH; kk+= TILESIZE)
            // Loop through the tile
            for(int i = ii; i < ii + TILESIZE && i < MATRIXLENGTH; i++) {
                for(int j = jj; j < jj + TILESIZE && j < MATRIXLENGTH; j++) {
                    // Loop through elements of current row and column combination
                    for(int k = kk; k < kk + TILESIZE && k < MATRIXLENGTH; k++) {
                        result[i][j] += matrix1[i][k] * matrix2[k][j];
                    }
                }
            }
        }
    }
    return 0;
}

void MTTiling() {
    thread threads[THREADCOUNT];

    auto startFill = chrono::high_resolution_clock::now();
    for(int i = 0; i < THREADCOUNT; i++) {
        threads[i] = thread(setMatrices, i);
    }

    for(auto& th: threads) {
        th.join();
    }
    auto endFill = chrono::high_resolution_clock::now();

    chrono::duration<double> durationFill = endFill - startFill;

    auto startCalc = chrono::high_resolution_clock::now();
    for(int i = 0; i <= THREADCOUNT; i++) {
        threads[i] = thread(calculateProductMTTiling, i);
    }

    for(auto& th: threads) {
        th.join();
    }
    auto endCalc = chrono::high_resolution_clock::now();

    chrono::duration<double> durationCalc = endCalc - startCalc;

    outFile << "## Multithreaded Mode using Tilling" << endl;
    outFile << "Matrix size:                        " << 
    MATRIXLENGTH << " x " << MATRIXLENGTH << "\n" << endl;
    outFile << "Result[0][0]:                       " << 
    result[0][0] << "\n" << endl;
    outFile << "Time elapsed to fill matrices:      " << 
    durationFill.count() << "\n" << endl;
    outFile << "Time elapsed to calculate product:  " << 
    durationCalc.count() << "\n" << endl;
}