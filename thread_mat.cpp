#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <pthread.h>

using namespace std;

const int N = 200; // Size of the matrices
const int NUM_THREADS = 6; // Number of threads to use

int A[N][N], B[N][N], C[N][N];
pthread_t threads[NUM_THREADS];

// Function to generate random values for the matrices
void generateRandomMatrix(int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % 100; // Generating random values between 0 and 99
        }
    }
}

// Struct to pass arguments to the thread function
struct ThreadData {
    int thread_id;
};

// Function to perform matrix multiplication for a specific range of rows
void* partialMatrixMultiplication(void* thread_arg) {
    ThreadData* data = (ThreadData*)thread_arg;
    int start = (N / NUM_THREADS) * data->thread_id;
    int end = (N / NUM_THREADS) * (data->thread_id + 1);

    for (int i = start; i < end; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    pthread_exit(NULL);
}

int main() {
    generateRandomMatrix(A);
    generateRandomMatrix(B);

    clock_t start_time = clock();

    for (int i = 0; i < NUM_THREADS; i++) {
        ThreadData* data = new ThreadData();
        data->thread_id = i;
        pthread_create(&threads[i], NULL, partialMatrixMultiplication, (void*)data);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_t end_time = clock();
    double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC;

    cout << "Matrix multiplication completed. Execution time: " << elapsed_time << " seconds." << endl;

    // Writing the output to a file
    ofstream outputFile("output_matrix_parallel_num_200.txt");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            outputFile << C[i][j] << " ";
        }
        outputFile << endl;
    }
    outputFile.close();

    return 0;
}
