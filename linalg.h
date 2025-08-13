#ifndef LINALG_H
#define LINALG_H

struct matrix {
    int *values;
    int height;
    int width;
};

struct matrix* create_matrix(const int* listofval, int height, int width);
void free_matrix(struct matrix* m);
struct matrix* matrix_mult(const struct matrix *m1, const struct matrix *m2);
void print_matrix(const struct matrix* m);

#endif // LINALG_H