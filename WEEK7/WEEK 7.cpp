#include <stdio.h>
#include <stdlib.h>

void gaussianElimination(double matrix[6][6], double* vector, int n) {
    for (int k = 0; k < n - 1; k++) {
        for (int i = k + 1; i < n; i++) {
            // Calculate elimination factor
            double factor = matrix[i][k] / matrix[k][k];

            for (int j = k; j < n; j++) {
                // Perform elimination operation
                matrix[i][j] -= factor * matrix[k][j];
            }

            // Update vector
            vector[i] -= factor * vector[k];
        }
    }

    // Array to store solution vector
    double* solution = (double*)malloc(n * sizeof(double));

    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;

        for (int j = i + 1; j < n; j++) {
            // Calculate the sum of products for solution vector
            sum += matrix[i][j] * solution[j];
        }

        // Calculate each element of solution vector
        solution[i] = (vector[i] - sum) / matrix[i][i];
    }

    printf("Solution:\n");

    for (int i = 0; i < n; i++) {
        // Print each element of solution vector
        printf("x%d = %lf\n", i + 1, solution[i]);
    }

    // Free memory allocated for solution vector
    free(solution);
}

int main() {
    double a, da, dda, b, db, ddb;

    printf("Enter the values of a, da, dda, b, db, ddb: ");
    scanf("%lf %lf %lf %lf %lf %lf", &a, &da, &dda, &b, &db, &ddb);

    int n = 6; // Matrix dimension

    // Initialize vector
    double* vector = (double*)malloc(n * sizeof(double));
    vector[0] = a;
    vector[1] = b;
    vector[2] = da;
    vector[3] = db;
    vector[4] = dda;
    vector[5] = ddb;

    // Coefficient matrix of the linear equation system
    double A[6][6] = {
        {1, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1},
        {0, 1, 0, 0, 0, 0},
        {0, 0, 2, 0, 0, 0},
        {0, 1, 2, 3, 4, 5},
        {0, 0, 2, 6, 12, 20}
    };

    // Solve the linear equation system using Gaussian elimination method
    gaussianElimination(A, vector, n);

    // Free memory allocated for vector
    free(vector);

    return 0;
}
