#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

typedef struct polynomial_s {
    unsigned deg;
    double *coeff;
} ply;

ply *ply_new (unsigned degree) {
    ply *new = malloc(sizeof(ply));
    new->deg = degree;
    new->coeff = malloc(sizeof(double) * degree);
    return new;
}