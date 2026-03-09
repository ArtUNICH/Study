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

void multiply_n_string_of_the_matrix_by_a_number_X(double** matrix, int size_of_matrix, int n, double X) {
    if (X == 0 || n > size_of_matrix || n < 1) {
        printf("Invalid input values!");
        return 1;
    }
    for (int i = 0; i < size_of_matrix; i++) {
        matrix[n - 1][i] = X * matrix[n - 1][i];
    }
}

void adding_n_string_to_m_string_of_the_matrix(double** matrix, int size_of_matrix, int n, int m) {
    if (n < 1 || m < 1 || n > size_of_matrix || m > size_of_matrix) {
        printf("Invalid input values!");
        return 1;
    }
    for (int i = 0; i < size_of_matrix; i++) {
        matrix[m - 1][i] = matrix[m - 1][i] + matrix[n - 1][i];
    }
}

void making_the_matrix_triangular(double** matrix, int size_of_matrix) {
    int j = 0;
    while (j < sizeof_matrix) {
        for (int i = 0; i < size_of_matrix - 1; i++) {
            if (matrix[i][j] = 0) {
                j++;
            } else {
                for (int next = i + 1; next < size_of_matrix; next++) {
                    if (matrix[next][j] != 0) {
                        double tmp_value = matrix[i][j];
                        multiply_n_string_of_the_matrix_by_a_number_X(matrix, size_of_matrix, i + 1, matrix[next][j]);
                        multiply_n_string_of_the_matrix_by_a_number_X(matrix, size_of_matrix, next + 1, -tmp_value);
                        adding_n_string_to_m_string_of_the_matrix(matrix, size_of_matrix, i + 1, next + 1);
                        matrix[i][j] = tmp_value;
                    }
                }
            }
        }
    }
}

double calculate_the_determinant(double** matrix, int size_of_matrix) {
    making_the_matrix_triangular(matrix, size_of_matrix);
    double result = 1;
    for (int i = 0; i < size_of_matrix; i++) {
        result = result * matrix[i][i];
    }
    return result;
}

int main() {
    int size_of_matrix;
    scanf("%d", &size_of_matrix);
    double** matrix = create_and_init_matrix(size_of_matrix);
    double determinant = calculate_the_determinant(matrix, size_of_matrix);
    printf("%lf", determinant);
    return 0;
