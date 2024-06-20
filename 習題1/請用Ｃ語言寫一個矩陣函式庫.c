#include <stdio.h>
#include <stdlib.h>

// Function to create a matrix
double** createMatrix(int rows, int cols) {
    double** matrix = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (double*)malloc(cols * sizeof(double));
    }
    return matrix;
}

// Function to free the matrix
void freeMatrix(double** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to transpose a matrix
double** transpose(double** matrix, int rows, int cols) {
    double** transposed = createMatrix(cols, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transposed[j][i] = matrix[i][j];
        }
    }
    return transposed;
}

// Function to add two matrices
double** add(double** matrix1, double** matrix2, int rows, int cols) {
    double** result = createMatrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    return result;
}

// Function to multiply two matrices
double** multiply(double** matrix1, int rows1, int cols1, double** matrix2, int rows2, int cols2) {
    if (cols1 != rows2) {
        printf("Matrices cannot be multiplied\n");
        return NULL;
    }
    double** result = createMatrix(rows1, cols2);
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < cols1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return result;
}

// Function to print a matrix
void dump(double** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to reshape a matrix (not implemented)
double** reshape(double** matrix, int rows, int cols, int new_rows, int new_cols) {
    // Reshape logic (not implemented)
    return NULL;
}

int main() {
    int rows = 2, cols = 3;
    double** matrix = createMatrix(rows, cols);
    // Fill the matrix with some values
    matrix[0][0] = 1.0; matrix[0][1] = 2.0; matrix[0][2] = 3.0;
    matrix[1][0] = 4.0; matrix[1][1] = 5.0; matrix[1][2] = 6.0;

    printf("Original matrix:\n");
    dump(matrix, rows, cols);

    double** transposed = transpose(matrix, rows, cols);
    printf("Transposed matrix:\n");
    dump(transposed, cols, rows);

    // Free allocated memory
    freeMatrix(matrix, rows);
    freeMatrix(transposed, cols);

    return 0;
}
