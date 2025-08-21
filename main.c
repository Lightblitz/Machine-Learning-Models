#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "linalg.h"

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#define MAX_CMD_LEN 31
#define MATRIX_COUNT 5
/*
// run_linear_regression takes the matrix X to solve for s = (X^TX)^-1X^Ty
char* run_linear_regression(const struct matrix* X, const struct matrix* Y, const int num_points) {
    for (int i = 0; i < num_points; i++) {
        
    }
} */

// Reads a command safely, returns 1 if successful, 0 if EOF
int read_command(char *cmd, size_t size) {
    if (scanf("%31s", cmd) != 1) {
        return 0;
    }
    if (strlen(cmd) >= size) {
        fprintf(stderr, "Error: Command length limit is %zu characters.\n", size - 1);
        // Clear the rest of the input buffer for safety
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
        return -1;
    }
    return 1;
}

// For functions that create matrices, remodel logic to require manual free of destination before calling the function
int main(void) {
    char cmd[MAX_CMD_LEN + 1];
    mat *matrices[MATRIX_COUNT] = { NULL };

    printf("Matrix CLI. Commands:\n");
    printf("mat_sqr <index> <dimension>\n");
    printf("mat_rnd <index> <rows> <cols> <min> <max>\n");
    printf("mat_identity <index> <dimension>\n");
    printf("mat_new <index> <rows> <cols>\n");
    printf("mat_print <index>\n");
    printf("mat_add <dest> <m1> <m2>\n");
    printf("mat_sub <dest> <m1> <m2>\n");
    printf("mat_mult <dest> <m1> <m2>\n");
    printf("free <index>\n");
    printf("exit\n");

    while (1) {
        printf("> ");
        int cmd_status = read_command(cmd, sizeof(cmd));
        if (cmd_status == 0) break; // EOF
        if (cmd_status == -1) continue; // too long, retry

        if (strcmp(cmd, "mat_sqr") == 0) {
            unsigned idx, dim;
            if (scanf("%u %u", &idx, &dim) == 2 && idx < MATRIX_COUNT) {
                mat_free(matrices[idx]);
                matrices[idx] = mat_sqr(dim);
                printf("Created square matrix #%u of dimension %u.\n", idx, dim);
            }

        } else if (strcmp(cmd, "mat_rnd") == 0) {
            unsigned idx, rows, cols;
            double min, max;
            if (scanf("%u %u %u %lf %lf", &idx, &rows, &cols, &min, &max) == 5 && idx < MATRIX_COUNT) {
                mat_free(matrices[idx]);
                matrices[idx] = mat_rnd(rows, cols, min, max);
                printf("Created random matrix #%u (%ux%u) in [%.2f, %.2f].\n", idx, rows, cols, min, max);
            }

        } else if (strcmp(cmd, "mat_identity") == 0) {
            unsigned idx, dim;
            if (scanf("%u %u", &idx, &dim) == 2 && idx < MATRIX_COUNT) {
                mat_free(matrices[idx]);
                matrices[idx] = mat_identity(dim);
                printf("Created identity matrix #%u of dimension %u.\n", idx, dim);
            }

        } else if (strcmp(cmd, "mat_new") == 0) {
            unsigned idx, rows, cols;
            if (scanf("%u %u %u", &idx, &rows, &cols) == 3 && idx < MATRIX_COUNT) {
                mat_free(matrices[idx]);
                matrices[idx] = mat_new(rows, cols);
                printf("Created new matrix #%u (%ux%u).\n", idx, rows, cols);
            }

        } else if (strcmp(cmd, "mat_print") == 0) {
            unsigned idx;
            if (scanf("%u", &idx) == 1 && idx < MATRIX_COUNT && matrices[idx]) {
                mat_print(matrices[idx]);
            } else {
                printf("Invalid index or matrix not initialized.\n");
            }

        } else if (strcmp(cmd, "mat_add") == 0) {
            unsigned dest, m1, m2;
            if (scanf("%u %u %u", &dest, &m1, &m2) == 3 &&
                dest < MATRIX_COUNT && m1 < MATRIX_COUNT && m2 < MATRIX_COUNT) {
                mat_free(matrices[dest]);
                matrices[dest] = mat_add(matrices[m1], matrices[m2]);
                printf("Matrix #%u = Matrix #%u + Matrix #%u\n", dest, m1, m2);
            }

        } else if (strcmp(cmd, "mat_sub") == 0) {
            unsigned dest, m1, m2;
            if (scanf("%u %u %u", &dest, &m1, &m2) == 3 &&
                dest < MATRIX_COUNT && m1 < MATRIX_COUNT && m2 < MATRIX_COUNT) {
                mat_free(matrices[dest]);
                matrices[dest] = mat_sub(matrices[m1], matrices[m2]);
                printf("Matrix #%u = Matrix #%u - Matrix #%u\n", dest, m1, m2);
            }

        } else if (strcmp(cmd, "mat_mult") == 0) {
            unsigned dest, m1, m2;
            if (scanf("%u %u %u", &dest, &m1, &m2) == 3 &&
                dest < MATRIX_COUNT && m1 < MATRIX_COUNT && m2 < MATRIX_COUNT) {
                mat_free(matrices[dest]);
                matrices[dest] = mat_mult(matrices[m1], matrices[m2]);
                printf("Matrix #%u = Matrix #%u * Matrix #%u\n", dest, m1, m2);
            }

        } else if (strcmp(cmd, "mat_neg") == 0) {
            unsigned dest, src;
            if (scanf("%u %u", &dest, &src) == 2 &&
                dest < MATRIX_COUNT && src < MATRIX_COUNT && matrices[src]) {
                if (matrices[dest]) {
                    printf("Error: destination #%u not freed. Use 'free %u' first.\n", dest, dest);
                } else {
                    matrices[dest] = mat_neg(matrices[src]);
                    printf("Matrix #%u = -Matrix #%u\n", dest, src);
                }
            }

        } else if (strcmp(cmd, "mat_transpose") == 0) {
            unsigned dest, src;
            if (scanf("%u %u", &dest, &src) == 2 &&
                dest < MATRIX_COUNT && src < MATRIX_COUNT && matrices[src]) {
                if (matrices[dest]) {
                    printf("Error: destination #%u not freed. Use 'free %u' first.\n", dest, dest);
                } else {
                    matrices[dest] = mat_transpose(matrices[src]);
                    printf("Matrix #%u = (Matrix #%u)^T\n", dest, src);
                }
            }

        } else if (strcmp(cmd, "ero_scalar") == 0) {
            unsigned idx;
            int row;
            double scalar;
            if (scanf("%u %d %lf", &idx, &row, &scalar) == 3 &&
                idx < MATRIX_COUNT && matrices[idx]) {
                mat_ero_scalar(matrices[idx], row, scalar);
                printf("Scaled row %d of Matrix #%u by %.2f\n", row, idx, scalar);
            }

        } else if (strcmp(cmd, "ero_swap") == 0) {
            unsigned idx;
            int r1, r2;
            if (scanf("%u %d %d", &idx, &r1, &r2) == 3 &&
                idx < MATRIX_COUNT && matrices[idx]) {
                mat_ero_swap(matrices[idx], r1, r2);
                printf("Swapped rows %d and %d of Matrix #%u\n", r1, r2, idx);
            }

        } else if (strcmp(cmd, "ero_add") == 0) {
            unsigned idx;
            int r1, r2;
            double scalar;
            if (scanf("%u %d %d %lf", &idx, &r1, &r2, &scalar) == 4 &&
                idx < MATRIX_COUNT && matrices[idx]) {
                mat_ero_add(matrices[idx], r1, r2, scalar);
                printf("Added %.2lf * row %d into row %d of Matrix #%u\n", scalar, r2, r1, idx);
            }
        } else if (strcmp(cmd, "ref") == 0) {
            unsigned dest, src;
            if (scanf("%u %u", &dest, &src) == 2 && dest < MATRIX_COUNT && src < MATRIX_COUNT && matrices[src]) {
                if (matrices[dest]) {
                    printf("Error: destination #%u not freed. Use 'free %u' first.\n", dest, dest);
                } else {
                    matrices[dest] = mat_ref(matrices[src]);
                    printf("Matrix #%u = REF of Matrix #%u\n", dest, src);
                }
            }
        } else if (strcmp(cmd, "rref") == 0) {
            unsigned dest, src;
            if (scanf("%u %u", &dest, &src) == 2 && dest < MATRIX_COUNT && src < MATRIX_COUNT && matrices[src]) {
                if (matrices[dest]) {
                    printf("Error: destination #%u not freed. Use 'free %u' first.\n", dest, dest);
                } else {
                    matrices[dest] = mat_rref(matrices[src]);
                    printf("Matrix #%u = REF of Matrix #%u\n", dest, src);
                }
            }
        } else if (strcmp(cmd, "free") == 0) {
            unsigned idx;
            if (scanf("%u", &idx) == 1 && idx < MATRIX_COUNT) {
                mat_free(matrices[idx]);
                // matrices[idx] = NULL;
                printf("Matrix #%u freed.\n", idx);
            }

        } else if (strcmp(cmd, "exit") == 0) {
            break;

        } else {
            printf("Unknown command.\n");
            // clear remaining input for safety
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
    }

    // Cleanup
    for (unsigned i = 0; i < MATRIX_COUNT; i++) {
        mat_free(matrices[i]);
    }
    return 0;
}
