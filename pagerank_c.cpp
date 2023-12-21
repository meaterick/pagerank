#include <stdio.h>
#include <random>

const int a = 5;//행렬 크기 설정

void matrix_multiply(double A[a][a], double B[a], double result[a]) {
    for (int i = 0; i < a; i++) {
        result[i] = 0.0;
        for (int j = 0; j < a; j++) {
            result[i] += A[i][j] * B[j];
            printf("%f ", result[i]);
        }
        printf("\n");
    }
}

void calculateTransitionMatrix(double A[a][a], double T[][a]) {
    // Iterate over columns
    for (int j = 0; j < a; j++) {
        // Calculate the sum of elements in the column
        double columnSum = 0;
        for (int i = 0; i < a; i++) {
            columnSum += A[j][i];
        }
        for (int i = 0; i < a; i++) {
            if (A[j][i] == 0) {
                T[j][i] = 0.0;
            }
            else {
                T[j][i] = 1.0 / columnSum;
            }
        }
    }
}

int main() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 1);//메르센 트위스터 난수 생성

    double M[a][a];

    double L[a][a];

    double x[a];

    double result[a];

    for (int i = 0; i < a; i++) {
        x[i] = 1.0 / (double)a;
    }

    for (int i = 0; i < a; i++) {
        for (int j = 0; j < a; j++) {
            M[i][j] = (double)dist(mt);
        }
    }//M 0-1 random 지정

    calculateTransitionMatrix(M, L);

    for (int i = 0; i < a; i++) {
        for (int j = 0; j < a; j++) {
            printf("%f ", L[i][j]);
        }
        printf("\n");
    }//L 출력

    for (int k = 0; k < 40; k++) {
        matrix_multiply(L, x, result);

        printf("Iteration %d: [", k);
        for (int i = 0; i < a; i++) {
            //printf("%f ", result[i]);
        }
        printf("]\n");

        for (int i = 0; i < a; i++) {
            x[i] = result[i];
        }
    }

    return 0;
}
