#include <stdio.h>

void matrix_multiply(double A[5][5], double B[5], double result[5]) {
    for (int i = 0; i < 5; i++) {
        result[i] = 0.0;
        for (int j = 0; j < 5; j++) {
            result[i] += A[i][j] * B[j];
        }
    }
}

int main() {
    double M[5][5] = {
        {0, 1, 0, 1, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0}
    };

    double L[5][5] = {
        {0, 0, 0, 0, 0.5},
        {1.0/3, 0, 0, 0, 0},
        {1.0/3, 0.5, 0, 0, 0.5},
        {1.0/3, 0.5, 0, 0, 0},
        {0, 0, 1, 1, 0}
    };

    double x[5] = {0.2, 0.2, 0.2, 0.2, 0.2};
    double result[5];

    for (int k = 0; k < 40; k++) {
        matrix_multiply(L, x, result);

        // Print the result for each iteration
        printf("Iteration %d: [", k);
        for (int i = 0; i < 5; i++) {
            printf("%f ", result[i]);
        }
        printf("]\n");

        // Update x for the next iteration
        for (int i = 0; i < 5; i++) {
            x[i] = result[i];
        }
    }

    return 0;
}
