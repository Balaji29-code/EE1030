#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

void print_mat(int size, complex double mat[size][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("(%4.6f + %4.6fI) ", creal(mat[i][j]), cimag(mat[i][j]));
        }
        printf("\n");
    }
}

void matmul(int size, complex double mat1[size][size], complex double mat2[size][size], complex double result[size][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = 0 + 0*I;
            for (int k = 0; k < size; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

complex double norm_complex(int size, complex double vec_1[size][1]) {
    complex double norm = 0 + 0*I;
    for (int i = 0; i < size; i++) {
        norm += vec_1[i][0] * conj(vec_1[i][0]);
    }
    norm = csqrt(norm);
    return norm;
}

void normalized_mat(int size, complex double mat_A[size][1], complex double mat_Q[size][1], complex double norm) {
    for (int i = 0; i < size; i++) {
        mat_Q[i][0] = mat_A[i][0] / norm;
    }
}

void initialize_QR(int size, complex double Q[size][size], complex double R[size][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            Q[i][j] = R[i][j] = 0 + 0*I;
        }
    }
}

void QRdecomposition(int size, complex double A[size][size], complex double Q[size][size], complex double R[size][size]) {
    initialize_QR(size, Q, R);
    for (int k = 0; k < size; k++) {
        complex double norm = 0 + 0*I;
        for (int i = 0; i < size; i++) {
            norm += A[i][k] * conj(A[i][k]);
        }
        norm = csqrt(norm);
        for (int i = 0; i < size; i++) {
            Q[i][k] = A[i][k] / norm;
        }
        for (int j = k; j < size; j++) {
            complex double dot = 0 + 0*I;
            for (int i = 0; i < size; i++) {
                dot += conj(Q[i][k]) * A[i][j];
            }
            R[k][j] = dot;
            for (int i = 0; i < size; i++) {
                A[i][j] -= Q[i][k] * R[k][j];
            }
        }
    }
}

void QRwithShift(int size, complex double matrix[size][size], complex double eigenvalues[size]) {
    complex double Q[size][size], R[size][size];
    complex double shift;
    int converged;
    for (int iter = 0; iter < 1000; iter++) {
        if (size > 1) {
            complex double d = (matrix[size-2][size-2] - matrix[size-1][size-1]) / 2.0;
            complex double sign = (creal(d) >= 0) ? 1.0 + 0*I : -1.0 + 0*I;
            shift = matrix[size-1][size-1] - sign * csqrt(d * d + matrix[size-1][size-2] * matrix[size-2][size-1]);
        } else {
            shift = matrix[size-1][size-1];
        }
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                matrix[i][j] -= shift * (i == j);
            }
        }
        QRdecomposition(size, matrix, Q, R);
        matmul(size, R, Q, matrix);
        for (int i = 0; i < size; i++) {
            matrix[i][i] += shift;
        }
        converged = 1;
        for (int i = 0; i < size - 1; i++) {
            if (cabs(matrix[i + 1][i]) > 1e-9) {
                converged = 0;
                break;
            }
        }
        if (converged) {
            break;
        }
    }
    for (int i = 0; i < size; i++) {
        eigenvalues[i] = matrix[i][i];
    }
}

int main(void) {
    int size;
    printf("Enter the size of the matrix: ");
    scanf("%d", &size);

    complex double matrix[size][size];
    complex double eigenvalues[size];
    double real, imaginary;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("Enter the real part and imaginary part of the matrix[%d][%d]: ", i + 1, j + 1);
            scanf("%lf %lf", &real, &imaginary);
            matrix[i][j] = real + imaginary * I;
        }
    }

    printf("\nOriginal Matrix:\n");
    print_mat(size, matrix);

    QRwithShift(size, matrix, eigenvalues);

    printf("\nMatrix after QR Algorithm with Shift:\n");
    print_mat(size, matrix);

    printf("\nEigenvalues:\n");
    for (int i = 0; i < size; i++) {
        printf("(%4.6f + %4.6fI)\n", creal(eigenvalues[i]), cimag(eigenvalues[i]));
    }

    return 0;
}

