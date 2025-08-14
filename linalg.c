#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "math_func.h"
#include "errors.h"

// struct mat_s stores the data for a matrix structure
typedef struct mat_s {
    int row_count;
    int col_count;
    double **data; // data[i][j] <-> array[i*m + j]
    int is_square;
} mat;


// ---------------------------------------------------------------
// ---------------------------------------------------------------
// FOLLOWING FUNCTIONS CREATE AND DESTROY THE MATRIX ADT
// ---------------------------------------------------------------
// ---------------------------------------------------------------


// mat_new(num_rows, num_cols) allocates memory to create a new matrix
mat *mat_new(int num_rows, int num_cols) {
    if (num_rows == 0) {
        MAT_ERROR("mat_new() called with num_rows = 0");
        return NULL;
    }
    if (num_cols == 0) {
        MAT_ERROR("mat_new() called with num_cols = 0");
        return NULL;
    }
    mat *m = malloc(sizeof(mat));
    NP_CHECK(m);
    m->row_count = num_rows;
    m->col_count = num_cols;
    m->is_square = (num_cols == num_rows) ? 1: 0;
    m->data = calloc(m->row_count, sizeof(*m->data));
    NP_CHECK(m->data);

    for (int i = 0; i < m->row_count; i++) {
        m->data[i] = calloc(m->col_count, sizeof(double));
        NP_CHECK(m->data[i]);
    }
    return m;
}

// mat_free takes a pointer to a matrix and frees the memory
void mat_free(mat *matrix) {
    if (matrix == NULL) {
        return;
    }
    for (int i = 0; i < matrix->row_count; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
}

// mat_sqr takes a natural number and creates a square matrix with that dimension
mat *mat_sqr(int dimension) {
    if (dimension == 0) {
        MAT_ERROR("mat_sqr() called with dimension = 0");
        return NULL;
    }
    return mat_new(dimension, dimension);
}

// mat_rnd takes the dimensions of a matrix, along with a lower and upper bound
// and creates a matrix with entries generated randomly between the bounds
mat *mat_rnd(int num_rows, int num_cols, double min, double max) {
    if (num_rows == 0) {
        MAT_ERROR("mat_rnd() called with num_rows = 0");
        return NULL;
    }
    if (num_cols == 0) {
        MAT_ERROR("mat_rnd() called with num_cols = 0");
        return NULL;
    }
    mat *m = mat_new(num_rows, num_cols);
    for (int i = 0; i < m->row_count; i++) {
        for (int j = 0; j< m->col_count; j++) {
            m->data[i][j] = nml_rand_interval(min, max);// randomly generate from the interval [min, max]
        }
    }
    return m;
}

// mat_identity creates an identity matrix given a dimension
mat *mat_identity(int dimension) {
    if (dimension == 0) {
        MAT_ERROR("mat_identity() called with dimension = 0");
        return NULL;
    }
    mat *m = mat_new(dimension, dimension);
    for (int i = 0; i < dimension; i++) {
        m->data[i][i] = 1.0;
    }
    return m;
}

// ---------------------------------------------------------------
// ---------------------------------------------------------------
// PRINT FUNCTION PRINTS OUT A MATRIX
// ---------------------------------------------------------------
// ---------------------------------------------------------------

// mat_print prints out a matrix with each entry indicated in the format [i]
void mat_print(mat *matrix) {
    if (matrix == NULL) {
        MAT_ERROR("mat_print() called with NULL matrix");
        return;
    }
    int rows = matrix->row_count;
    int cols = matrix->col_count;
    for (int i = 0; i < rows; i++) {
        //printf("| ");
        for (int j = 0; j < cols; j++) {
            printf("[%.2lf]", matrix->data[i][j]);
        }
        printf("\n");
    }
    return;
}

// ---------------------------------------------------------------
// ---------------------------------------------------------------
// STANDARD MATRIX ARITHMETIC
// ---------------------------------------------------------------
// ---------------------------------------------------------------

// mat_add adds two matrices together and returns a pointer to the new matrix. Does not free memory
mat *mat_add(mat *m1, mat *m2) {
    if (m1 == NULL || m2 == NULL) {
        MAT_ERROR("mat_add() called with NULL pointers");
        return NULL;
    }
    if (m1->row_count == m2->row_count && m1->col_count == m2->col_count) {
        mat *dest = mat_new(m1->row_count, m1->col_count);
        for (int i = 0; i < m1->row_count; i++) {
            for (int j = 0; j < m1->col_count; j++) {
                dest->data[i][j] = m1->data[i][j] + m2->data[i][j]; 
            }
        }
        return dest;
    } else {
        MAT_ERROR("mat_add() called with matrices of different sizes");
        return NULL;
    }
}

// mat_sub subtracts two matrices and returns a pointer to the new matrix. Does not free memory
mat *mat_sub(mat *m1, mat *m2) {
    if (m1 == NULL || m2 == NULL) {
        MAT_ERROR("mat_sub() called with NULL pointers");
        return NULL;
    }
    if (m1->row_count == m2->row_count && m1->col_count == m2->col_count) {
        mat *dest = mat_new(m1->row_count, m1->col_count);
        for (int i = 0; i < m1->row_count; i++) {
            for (int j = 0; j < m1->col_count; j++) {
                dest->data[i][j] = m1->data[i][j] - m2->data[i][j]; 
            }
        }
        return dest;
    } else {
        MAT_ERROR("mat_sub() called with matrices of different sizes");
        return NULL;
    }
}

// mat_mult multiplies two matrices and returns a pointer to the new matrix. Does not free memory
mat *mat_mult(mat *m1, mat *m2) {
    if (m1 == NULL || m2 == NULL) {
        MAT_ERROR("mat_mult() called with NULL pointers");
        return NULL;
    }
    if (m1->col_count == m2->row_count) {
        mat *dest = mat_new(m1->row_count, m2->col_count);
        for (int i = 0; i < dest->row_count; i++) {
            for (int j = 0; j < dest->col_count; j++) {
                double sum = 0.0;
                for (int k = 0; k < m1->col_count; k++) {
                    sum += m1->data[i][k] * m2->data[k][j];
                }
                dest->data[i][j] = sum;
            }
        }
        return dest;
    } else {
        MAT_ERROR("mat_mult() called with invalid matrix sizes");
        return NULL;
    }
}