#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include <random>
#include <filesystem>
#include <chrono>
#include <windows.h>
#include "../include/SimpleTiling.hpp"
#include "../include/main.hpp"

using namespace std;

void setMatricesTiling() {
    // Fill up the matrices!
    for(int ii = 0; ii < MATRIXLENGTH; ii+=TILESIZE) {
        for(int jj = 0; jj < MATRIXLENGTH; jj+= TILESIZE) {
            for(int i = ii; i < ii + TILESIZE && i < MATRIXLENGTH; i++) {
                for(int j = jj; j < jj + TILESIZE && j < MATRIXLENGTH; j++) {
                    matrix1[i][j] = randomNumberGenerator(0, 99);
                    matrix2[i][j] = randomNumberGenerator(0, 99);
                    result[i][j] = 0;
                }
            }
        }
    }
}

// Calculate multiplicative product of the two matrices: matrix1 and matrix2
int calculateProductSMPLTiling() {
    // Loop through rows
    for(int ii = 0; ii < MATRIXLENGTH; ii+=TILESIZE) {
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

void SimpleTiling() {
    auto startFill = chrono::high_resolution_clock::now();
    setMatrices(-1);
    auto endFill = chrono::high_resolution_clock::now();

    chrono::duration<double> durationFill = endFill - startFill;

    auto startCalc = chrono::high_resolution_clock::now();
    calculateProductSMPLTiling();
    auto endCalc = chrono::high_resolution_clock::now();

    chrono::duration<double> durationCalc = endCalc - startCalc;

    outFile << "## Simple Mode using Tilling" << endl;
    outFile << "Matrix size:                        " << 
    MATRIXLENGTH << " x " << MATRIXLENGTH << "\n" << endl;
    outFile << "Result[0][0]:                       " << 
    result[0][0] << "\n" << endl;
    outFile << "Time elapsed to fill matrices:      " << 
    durationFill.count() << "\n" << endl;
    outFile << "Time elapsed to calculate product:  " << 
    durationCalc.count() << "\n" << endl;
}