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
            scanf("%lf", &value);
            matrix[i][j] = value;
        }
    }
    return matrix;
}

double multiply_n_string_of_the_matrix_by_a_number_X(double** matrix, int size_of_matrix, int n, double X) {
    if (X == 0 || n > size_of_matrix || n < 1) {
        printf("Invalid input values!\n");
        return 1.0;
    }
    for (int i = 0; i < size_of_matrix; i++) {
        matrix[n - 1][i] = X * matrix[n - 1][i];
    }
    return X; //matrix multiplier for the determinant
}

double adding_n_string_to_m_string_of_the_matrix(double** matrix, int size_of_matrix, int n, int m) {
    if (n < 1 || m < 1 || n > size_of_matrix || m > size_of_matrix) {
        printf("Invalid input values!\n");
        return 1.0;
    }
    for (int i = 0; i < size_of_matrix; i++) {
        matrix[m - 1][i] = matrix[m - 1][i] + matrix[n - 1][i];
    }
    return 1.0; //matrix multiplier for the determinant
}

double rearrange_lines_n_and_m_in_the_matrix(double** matrix, int size_of_matrix, int n, int m) {
    if (n < 1 || m < 1 || n > size_of_matrix || m > size_of_matrix) {
        printf("Invalid input values!\n");
        return 1.0;
    }
    for (int i = 0; i < size_of_matrix; i++) {
        double tmp_value = matrix[n - 1][i];
        matrix [n - 1][i] = matrix[m - 1][i];
        matrix[m - 1][i] = tmp_value;
    }
    return -1.0; //matrix multiplier for the determinant
}

double making_the_matrix_triangular(double** matrix, int size_of_matrix) {
    double matrix_multiplier_for_the_determinant = 1;
    int j = 0;
    for (int i = 0; i < size_of_matrix; i++) {
        if (matrix[i][j] == 0) {
            for (int next = i + 1; next < size_of_matrix; next++) {
                if (matrix[next][j] != 0) {
                    matrix_multiplier_for_the_determinant *= rearrange_lines_n_and_m_in_the_matrix(matrix, size_of_matrix, i + 1, next + 1);
                    next = size_of_matrix; //exit from for cycle
                }
            }
        }
        if (matrix[i][j] != 0) {
            for (int next = i + 1; next < size_of_matrix; next++) {
                if (matrix[next][j] != 0) {
                    double innaccuracy_in_changing_determinant = multiply_n_string_of_the_matrix_by_a_number_X(matrix, size_of_matrix, next + 1, -matrix[i][j]/matrix[next][j]);
                    matrix_multiplier_for_the_determinant *= adding_n_string_to_m_string_of_the_matrix(matrix, size_of_matrix, i + 1, next + 1);
                    matrix_multiplier_for_the_determinant /= innaccuracy_in_changing_determinant;
                }
            }
        }
        j++;
    }
    return matrix_multiplier_for_the_determinant;
}

double calculate_the_determinant(double** matrix, int size_of_matrix) {
    double matrix_multiplier_for_the_determinant = making_the_matrix_triangular(matrix, size_of_matrix);
    double result = 1;
    for (int i = 0; i < size_of_matrix; i++) {
        result *= matrix[i][i];
    }
    return result * matrix_multiplier_for_the_determinant;
}

int main() {
    int size_of_matrix;
    scanf("%d", &size_of_matrix);
    double** matrix = create_and_init_matrix(size_of_matrix);
    double determinant = calculate_the_determinant(matrix, size_of_matrix);
    printf("%lf\n", determinant);
    return 0;
}