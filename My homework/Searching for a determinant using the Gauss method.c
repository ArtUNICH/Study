#include <stdio.h>
#include <stdlib.h>

double** create_and_init_matrix(int size_of_matrix) {
    double** matrix = (double**)malloc(size_of_matrix * sizeof(double*));
    for (int i = 0; i < size_of_matrix; i++) {
        matrix[i] = (double*)malloc(size_of_matrix * sizeof(double));
    }

    for (int i = 0; i < size_of_matrix; i++) {
        for (int j = 0; j < size_of_matrix; j++) {
            double value;
            scanf("lf", &value);
            double[i][j] = value;
        }
    }
    return matrix;
}

void making_the_matrix_triangular(int size_of_matrix, double** matrix) {
    for (int i = 1; i < size_of_matrix; i++) {
        
    }
}

int main() {
    int size_of_matrix;
    scanf("%d", &size_of_matrix);
    double** matrix = create_and_init_matrix(size_of_matrix);


    return 0;
