#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <random>
#include <filesystem>
#include <chrono>

using namespace std;

// Stores the one dimensional size of the matrix
const int MATRIXLENGTH = 500;
// Creates matrices of MATRIXLENGTH in length and width! Thus the size of the matrix is MATRIXLENGTH^2
int matrix1[MATRIXLENGTH][MATRIXLENGTH];
int matrix2[MATRIXLENGTH][MATRIXLENGTH];

long dotProduct = 0;

// Create a random number generator with an upper and lower bound! (inclusive)
int randomNumberGenerator(int lower_bound, int upper_bound) {
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> distr(lower_bound, upper_bound);

    return distr(gen);
}

void fillMatrices() {

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
    fillMatrices();
    auto endFill = chrono::high_resolution_clock::now();

    chrono::duration<double> durationFill = endFill - startFill;

    cout << "FINISHED FILLING UP MATRICES" << endl;

    auto startCalc = chrono::high_resolution_clock::now();
    calculateProduct();
    auto endCalc = chrono::high_resolution_clock::now();

    chrono::duration<double> durationCalc = endCalc - startCalc;


    cout << dotProduct << endl;
    cout << "Time elapsed to fill: " << durationFill.count() << endl;
    cout << "Time elapsed to calculate: " << durationCalc.count() << endl;
}
void fillMatrices()
{
    // Fill up the matrices!
    for (int i = 0; i < MATRIXLENGTH; i++)
    {
        for (int j = 0; j < MATRIXLENGTH; j++)
        {
            matrix1[i][j] = randomNumberGenerator(0, 99);
            matrix2[i][j] = randomNumberGenerator(0, 99);
        }
    }
}