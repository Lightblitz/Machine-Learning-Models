#ifndef LINALG_H
#define LINALG_H

#include <stddef.h>  // for size_t

typedef struct mat_s {
    int row_count;
    int col_count;
    double **data; // data[i][j]
    int is_square;
} mat;

// MATRIX CREATION AND DESTRUCTION
mat *mat_new(int num_rows, int num_cols);
void mat_free(mat *matrix);
mat *mat_sqr(int dimension);
mat *mat_rnd(int num_rows, int num_cols, double min, double max);
mat *mat_identity(int dimension);

// PRINT FUNCTION
void mat_print(mat *matrix);

// ARITHMETIC OPERATIONS ON MATRICES
mat *mat_add(const mat *m1, const mat *m2);
mat *mat_sub(const mat *m1, const mat *m2);
mat *mat_mult(const mat *m1, const mat *m2);
#endif // LINALG_H