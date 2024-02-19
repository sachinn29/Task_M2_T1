#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int N = 100; // Size of the matrices

// Function to generate random values for the matrices
void generateRandomMatrix(int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % 100; // Generating random values between 0 and 99
        }
    }
}

// Function to perform matrix multiplication
void matrixMultiplication(int A[N][N], int B[N][N], int C[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int A[N][N], B[N][N], C[N][N];
    generateRandomMatrix(A);
    generateRandomMatrix(B);

    clock_t start_time = clock();
    matrixMultiplication(A, B, C);
    clock_t end_time = clock();

    double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC;

    cout << "Matrix multiplication completed. Execution time: " << elapsed_time << " seconds." << endl;

    // Writing the output to a file
    ofstream outputFile("output_matrix.txt");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            outputFile << C[i][j] << " ";
        }
        outputFile << endl;
    }
    outputFile.close();

    return 0;
}
