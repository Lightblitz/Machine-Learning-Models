#ifndef LINALG_H
#define LINALG_H

#include <stddef.h>  // for size_t

typedef struct mat_s {
    int row_count;
    int col_count;
    double **data; // data[i][j]
    int is_square;
} mat;

// Matrix creation and destruction
mat *mat_new(int num_rows, int num_cols);
void mat_free(mat *matrix);
mat *mat_sqr(int dimension);
mat *mat_rnd(int num_rows, int num_cols, double min, double max);
mat *mat_identity(int dimension);
void mat_print(mat *matrix);

#endif // LINALG_H