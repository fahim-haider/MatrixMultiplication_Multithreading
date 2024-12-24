#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include <random>
#include <filesystem>
#include <chrono>

using namespace std;

// Stores the one dimensional size of the matrix
const int MATRIXLENGTH = 1000;
// Creates matrices of MATRIXLENGTH in length and width! Thus the size of the matrix is MATRIXLENGTH^2
int matrix1[MATRIXLENGTH][MATRIXLENGTH];
int matrix2[MATRIXLENGTH][MATRIXLENGTH];

long dotProduct = 0;

int THREADCOUNT = 4;

// Create a random number generator with an upper and lower bound! (inclusive)
int randomNumberGenerator(int lower_bound, int upper_bound) {
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> distr(lower_bound, upper_bound);

    return distr(gen);
}

void fillMatrices(int threadID) {
    // Fill up the matrices!
    for (int i = threadID - 1; i < MATRIXLENGTH; i += THREADCOUNT) {
        for (int j = threadID - 1; j < MATRIXLENGTH; j += THREADCOUNT) {
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

int main (int argc, char* argv[]) {
    cout << "TEST" << endl;

    auto startFill = chrono::high_resolution_clock::now();
    thread t1(fillMatrices, 1);
    thread t2(fillMatrices, 2);
    thread t3(fillMatrices, 3);
    thread t4(fillMatrices, 4);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    auto endFill = chrono::high_resolution_clock::now();

    chrono::duration<double> durationFill = endFill - startFill;

    cout << "FINISHED FILLING UP MATRICES" << endl;

    auto startCalc = chrono::high_resolution_clock::now();
    calculateProduct();
    auto endCalc = chrono::high_resolution_clock::now();

    chrono::duration<double> durationCalc = endCalc - startCalc;


    cout << "The dot product of the two randomly generated matrices is: " << dotProduct << endl;
    cout << "Time elapsed to fill: " << durationFill.count() << endl;
    cout << "Time elapsed to calculate: " << durationCalc.count() << endl;
}