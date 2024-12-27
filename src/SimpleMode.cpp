#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include <random>
#include <filesystem>
#include <chrono>
#include <windows.h>
#include "../include/SimpleMode.hpp"
#include "../include/main.hpp"

using namespace std;

// Calculate multiplicative product of the two matrices: matrix1 and matrix2
int calculateProductSimple() {
    // Loop through rows
    for(int i = 0; i < MATRIXLENGTH; i++) {
        // Loop through columns
        for(int j = 0; j < MATRIXLENGTH; j++) {
            long temp = 0;
            result[i][j] = 0;
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

// Acts as main for the simple mode!
void SimpleMode() {
    auto startFill = chrono::high_resolution_clock::now();
    fillMatrices(-1);
    auto endFill = chrono::high_resolution_clock::now();

    chrono::duration<double> durationFill = endFill - startFill;

    auto startCalc = chrono::high_resolution_clock::now();
    calculateProductSimple();
    auto endCalc = chrono::high_resolution_clock::now();

    chrono::duration<double> durationCalc = endCalc - startCalc;

    outFile << "## Simple Mode" << endl;
    outFile << "Matrix size:                        " << 
    MATRIXLENGTH << " x " << MATRIXLENGTH << "\n" << endl;
    outFile << "Result[0][0]:                       " << 
    result[0][0] << "\n" << endl;
    outFile << "Time elapsed to fill matrices:      " << 
    durationFill.count() << "\n" << endl;
    outFile << "Time elapsed to calculate product:  " << 
    durationCalc.count() << "\n" << endl;
}