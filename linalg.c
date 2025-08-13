#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "math_func.h"

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
        fprintf(stderr, "Error: mat_new() called with zero rows\n");
        exit(EXIT_FAILURE);
    }
    if (num_cols == 0) {
        fprintf(stderr, "Error: mat_new() called with zero columns\n");
        exit(EXIT_FAILURE);
    }
    mat *m = malloc(sizeof(mat));
    m->row_count = num_rows;
    m->col_count = num_cols;
    m->is_square = (num_cols == num_rows) ? 1: 0;
    m->data = calloc(m->row_count, sizeof(*m->data));

    for (int i = 0; i < m->row_count; i++) {
        m->data[i] = calloc(m->col_count, sizeof(double));
    }
    return m;
}

// mat_free takes a pointer to a matrix and frees the memory
void mat_free(mat *matrix) {
    assert(matrix);
    for (int i = 0; i < matrix->row_count; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
}

// mat_sqr takes a natural number and creates a square matrix with that dimension
mat *mat_sqr(int dimension) {
    assert(dimension > 0);
    return mat_new(dimension, dimension);
}

// mat_rnd takes the dimensions of a matrix, along with a lower and upper bound
// and creates a matrix with entries generated randomly between the bounds
mat *mat_rnd(int num_rows, int num_cols, double min, double max) {
    assert(num_rows > 0);
    assert(num_cols > 0);
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
    assert (dimension > 0);
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

void mat_print(mat *matrix) {
    int rows = matrix->row_count;
    int cols = matrix->col_count;
    for (int i = 0; i < rows; i++) {
        printf("| ");
        for (int j = 0; j < cols; j++) {
            printf("%lf ", matrix->data[i][j]);
        }
        printf("|\n");
    }
    return;
}