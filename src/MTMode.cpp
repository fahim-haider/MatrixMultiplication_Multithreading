#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include <random>
#include <filesystem>
#include <chrono>
#include <windows.h>
#include "../include/MTMode.hpp"
#include "../include/main.hpp"

using namespace std;

// Calculate multiplicative product of the two matrices: matrix1 and matrix2
int calculateProductMT(int threadID) {
    // Loop through rows
    for(int i = threadID; i < MATRIXLENGTH; i += THREADCOUNT) {
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

// Acts as main for the multithreading mode!
void MTMode() {
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
    for(int i = 0; i < THREADCOUNT; i ++) {
        threads[i] = thread(calculateProductMT, i);
    }

    for(auto& th: threads) {
        th.join();
    }
    auto endCalc = chrono::high_resolution_clock::now();

    chrono::duration<double> durationCalc = endCalc - startCalc;

    outFile << "## Multithreading Mode" << endl;
    outFile << "Matrix size:                        " << 
    MATRIXLENGTH << " x " << MATRIXLENGTH << endl;
    outFile << "Result[0][0]:                       " << 
    result[0][0] << endl;
    outFile << "Time elapsed to fill matrices:      " << 
    durationFill.count() << endl;
    outFile << "Time elapsed to calculate product:  " << 
    durationCalc.count() << "\n" << endl;
}