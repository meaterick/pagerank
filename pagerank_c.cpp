#include <stdio.h>
#include <random>
#include <time.h>

const int a = 252;//행렬 크기 설정

void printMatrix(double matrix[a]) {
    for (int i = 0; i < a; ++i) {
            printf("%.4f ", matrix[i]);
    }
    printf("\n");
}


void matrixPower_after(double matrix[a][a], int exponent, double result[a][a]) {
    for (int i = 0; i < a; ++i) {
        for (int j = 0; j < a; ++j) {
            result[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    for (int k = 0; k < exponent; ++k) {
        double temp;
        for (int j = 0; j < a; ++j) {
            for (int i = 0; i < a; ++i) {
                temp = result[i][j];
            }
        }

        for (int i = 0; i < a; ++i) {
            for (int j = 0; j < a; ++j) {
                result[i][j] = 0;
                for (int k = 0; k < a; ++k) {
                	if (matrix[i][k] == 0) {
                		result[i][j] = 0;
					} else {
						result[i][j] += matrix[i][k] * temp;
					}
                    
                }
            }
        }
    }
}

void matrixPower_before(double matrix[a][a], int exponent, double result[a][a]) {
    for (int i = 0; i < a; ++i) {
        for (int j = 0; j < a; ++j) {
            result[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    for (int k = 0; k < exponent; ++k) {
        double temp[a][a];
        for (int j = 0; j < a; ++j) {
            for (int i = 0; i < a; ++i) {
                temp[i][j] = result[i][j];
            }
        }

        for (int i = 0; i < a; ++i) {
            for (int j = 0; j < a; ++j) {
                result[i][j] = 0;
                for (int k = 0; k < a; ++k) {
					result[i][j] += matrix[i][k] * temp[k][j];
                }
            }
        }
    }
}


void dotProduct3(double matrix[a][a], double matrix1[a], double result[a]) {
    for (int i = 0; i < a; ++i) {
        result[i] = 0;
        for (int j = 0; j < a; ++j) {
            result[i] += matrix[i][j] * matrix1[j];
        }
    }
}

void calculateTransitionMatrix(double A[a][a], double T[a][a]) {
    double _T[a][a];
    for (int j = 0; j < a; j++) {
        double columnSum = 0;
        for (int i = 0; i < a; i++) {
            columnSum += A[j][i];
        }
        for (int i = 0; i < a; i++) {
            if (A[j][i] == 0) {
                _T[j][i] = 0.0;
            }
            else {
                _T[j][i] = 1.0 / columnSum;
            }
        }
    }

    for (int j = 0; j < a; j++) {
        for (int i = 0; i < a; i++) {
            T[j][i] = _T[i][j];
        }
    }
}

int main() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 3);//메르센 트위스터 난수 생성

    double M[a][a];

    double L[a][a];

    double x[a];

    double result[a][a];

    double _result[a];

    for (int i = 0; i < a; i++) {
        x[i] = 1.0 / (double)a;
    }

    for (int i = 0; i < a; i++) {
        for (int j = 0; j < a; j++) {
            if ((double)dist(mt) > 0) {
                M[i][j] = 1;
            }
            else {
                M[i][j] = 0;
            }
        }
    }//M 0-1 random 지정

    calculateTransitionMatrix(M, L);

//    for (int i = 0; i < a; i++) {
//        for (int j = 0; j < a; j++) {
//            printf("%f ", L[i][j]);
//        }
//        printf("\n");
//    }//L 출력
    
    
    clock_t start1 = clock();
    for (int k = 0; k < 40; ++k) {
        matrixPower_before(L, k, result);

        dotProduct3(result, x, _result);

//        printf("Iteration %d:\n", k);
//        printMatrix(_result);
    }
    
    clock_t end1 = clock();
    printf("소요 시간(최적화전): %lfs\n", (double)(end1 - start1) / CLOCKS_PER_SEC);
    
    
    clock_t start2 = clock();
    for (int k = 0; k < 40; ++k) {
        matrixPower_after(L, k, result);

        dotProduct3(result, x, _result);

//        printf("Iteration %d:\n", k);
//        printMatrix(_result);
    }
    
    clock_t end2 = clock();
    printf("소요 시간(최적화후): %lfs\n", (double)(end2 - start2) / CLOCKS_PER_SEC);
}
