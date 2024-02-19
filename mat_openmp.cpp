#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <omp.h>

using namespace std;

const int N = 100; // Size of the matrices

int A[N][N], B[N][N], C[N][N];

// Function to generate random values for the matrices
void generateRandomMatrix(int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % 100; // Generating random values between 0 and 99
        }
    }
}

int main() {
    generateRandomMatrix(A);
    generateRandomMatrix(B);

    clock_t start_time = clock();

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    clock_t end_time = clock();
    double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC;

    cout << "Matrix multiplication completed. Execution time: " << elapsed_time << " seconds." << endl;

    // Writing the output to a file
    ofstream outputFile("output_matrix_openmp.txt");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            outputFile << C[i][j] << " ";
        }
        outputFile << endl;
    }
    outputFile.close();

    return 0;
}
