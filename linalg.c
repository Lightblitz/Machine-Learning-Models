#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "math_func.h"

// struct mat_s stores the data for a matrix structure
typedef struct mat_s {
    unsigned int row_count;
    unsigned int col_count;
    double **data; // data[i][j] <-> array[i*m + j]
    int is_square;
} mat;


// ---------------------------------------------------------------
// ---------------------------------------------------------------
// FOLLOWING FUNCTIONS CREATE AND DESTROY THE MATRIX ADT
// ---------------------------------------------------------------
// ---------------------------------------------------------------


// mat_new(num_rows, num_cols) allocates memory to create a new matrix
mat *mat_new(unsigned int num_rows, unsigned int num_cols) {
    /*
    if (num_rows == 0) {
        // NML_ERROR(INVALID_ROWS);
        return NULL;
    }
    if (num_cols == 0) {
        // NML_ERROR(INVALID_COLS);
        return NULL;
    }
    */
    assert(num_rows > 0);
    assert(num_cols > 0);
    mat *m = malloc(sizeof(mat));
    // NP_CHECK(m);
    m->row_count = num_rows;
    m->col_count = num_cols;
    m->is_square = (num_cols == num_rows) ? 1: 0;
    m->data = calloc(m->row_count, sizeof(*m->data));

    for (int i = 0; i < m->row_count; i++) {
        m->data[i] = calloc(m->col_count, sizeof(double));
        // NP_CHECK(m->data[i]);
    }
    return m;
}

// mat_free takes a pointer to a matrix and frees the memory
void mat_free(mat *matrix) {
    for (int i = 0; i < matrix->row_count; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
}

// mat_sqr takes a natural number and creates a square matrix with that dimension
mat *mat_sqr(unsigned int dimension) {
    assert(dimension > 0);
    /*
    if (dimension == 0) {
        NML_ERROR(INVALID_ROWS);
    }
    */
    /*
    mat *m = malloc(sizeof(mat));
    m->row_count = dimension;
    m->col_count = dimension;
    m->is_square = 1;
    m->data = calloc(m->row_count, sizeof(*m->data));
    for (int i = 0; i < dimension; i++) {
        m->data[i] = calloc(m->col_count, sizeof(double));
    }
    return m;
    */
   return mat_new(dimension, dimension);
}

// mat_rnd takes the dimensions of a matrix, along with a lower and upper bound
// and creates a matrix with entries generated randomly between the bounds
mat *mat_rnd(unsigned int num_rows, unsigned int num_cols, double min, double max) {
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
mat *mat_identity(unsigned int dimension) {
    assert (dimension > 0);
    mat *m = mat_new(dimension, dimension);
    for (int i = 0; i < dimension; i++) {
        m->data[i][i] = 1.0;
    }
    return m;
}

