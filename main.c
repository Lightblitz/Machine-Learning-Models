#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "linalg.h"


/*
// run_linear_regression takes the matrix X to solve for s = (X^TX)^-1X^Ty
char* run_linear_regression(const struct matrix* X, const struct matrix* Y, const int num_points) {
    for (int i = 0; i < num_points; i++) {
        
    }
} */


int main() {
    char cmd[32];
    mat *current_mat = mat_new(1, 1);

    printf("Matrix CLI. Commands:\n");
    printf("mat_sqr <dimension>\n");
    printf("mat_rnd <rows> <cols> <min> <max>\n");
    printf("mat_identity <dimension>\n");
    printf("free\n");
    printf("exit\n");

    while (1) {
        printf("> ");
        if (scanf("%31s", cmd) != 1) break;

        if (strcmp(cmd, "mat_sqr") == 0) {
            unsigned int dim;
            if (scanf("%u", &dim) == 1) {
                mat_free(current_mat);
                current_mat = mat_sqr(dim);
                printf("Created square matrix of dimension %u:\n", dim);
                // You can add a print_matrix function to linalg.h/c to display the matrix
            }
        } else if (strcmp(cmd, "mat_rnd") == 0) {
            unsigned int rows, cols;
            double min, max;
            if (scanf("%u %u %lf %lf", &rows, &cols, &min, &max) == 4) {
                mat_free(current_mat);
                current_mat = mat_rnd(rows, cols, min, max);
                printf("Created random matrix %ux%u in [%.2f, %.2f]:\n", rows, cols, min, max);
            }
        } else if (strcmp(cmd, "mat_identity") == 0) {
            unsigned int dim;
            if (scanf("%u", &dim) == 1) {
                mat_free(current_mat);
                current_mat = mat_identity(dim);
                printf("Created identity matrix of dimension %u:\n", dim);
            }
        } else if (strcmp(cmd, "mat_new") == 0) {
            unsigned int rows, cols;
            if (scanf("%u %u", &rows, &cols) == 2) {
                mat_free(current_mat);
                current_mat = mat_new(rows, cols);
                printf("Created new matrix %ux%u:\n", rows, cols);
            }
        }else if (strcmp(cmd, "free") == 0) {
            mat_free(current_mat);
            current_mat = NULL;
            printf("Matrix freed.\n");
        } else if (strcmp(cmd, "mat_print") == 0) {
            mat_print(current_mat);
        } else if (strcmp(cmd, "exit") == 0) {
            break;
        } else {
            printf("Unknown command.\n");
        }
    }
    mat_free(current_mat);
    return 0;
}