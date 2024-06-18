#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

typedef struct {
    int *row_ptr;
    int *col_idx;
    double *values;
    int nrows;
    int ncols;
    int nnz;
} SparseMatrixCSR;

typedef struct {
    int *col_ptr;
    int *row_idx;
    double *values;
    int nrows;
    int ncols;
    int nnz;
} SparseMatrixCSC;

SparseMatrixCSR* read_sparse_matrix_csr(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Could not open file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    int nrows, ncols, nnz;
    fscanf(file, "%d %d %d", &nrows, &ncols, &nnz);

    SparseMatrixCSR *matrix = (SparseMatrixCSR*)malloc(sizeof(SparseMatrixCSR));
    matrix->nrows = nrows;
    matrix->ncols = ncols;
    matrix->nnz = nnz;
    matrix->row_ptr = (int*)malloc((nrows + 1) * sizeof(int));
    matrix->col_idx = (int*)malloc(nnz * sizeof(int));
    matrix->values = (double*)malloc(nnz * sizeof(double));

    for (int i = 0; i <= nrows; i++) {
        fscanf(file, "%d", &matrix->row_ptr[i]);
    }
    for (int i = 0; i < nnz; i++) {
        fscanf(file, "%d", &matrix->col_idx[i]);
    }
    for (int i = 0; i < nnz; i++) {
        fscanf(file, "%lf", &matrix->values[i]);
    }

    fclose(file);
    return matrix;
}

SparseMatrixCSC* read_sparse_matrix_csc(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Could not open file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    int nrows, ncols, nnz;
    fscanf(file, "%d %d %d", &nrows, &ncols, &nnz);

    SparseMatrixCSC *matrix = (SparseMatrixCSC*)malloc(sizeof(SparseMatrixCSC));
    matrix->nrows = nrows;
    matrix->ncols = ncols;
    matrix->nnz = nnz;
    matrix->col_ptr = (int*)malloc((ncols + 1) * sizeof(int));
    matrix->row_idx = (int*)malloc(nnz * sizeof(int));
    matrix->values = (double*)malloc(nnz * sizeof(double));

    for (int i = 0; i <= ncols; i++) {
        fscanf(file, "%d", &matrix->col_ptr[i]);
    }
    for (int i = 0; i < nnz; i++) {
        fscanf(file, "%d", &matrix->row_idx[i]);
    }
    for (int i = 0; i < nnz; i++) {
        fscanf(file, "%lf", &matrix->values[i]);
    }

    fclose(file);
    return matrix;
}

void multiply_sparse_matrices(const SparseMatrixCSR *A, const SparseMatrixCSC *B, double **C, int nrows, int ncols) {
    #pragma omp parallel for
    for (int i = 0; i < nrows; i++) {
        for (int j = A->row_ptr[i]; j < A->row_ptr[i + 1]; j++) {
            int colA = A->col_idx[j];
            double valA = A->values[j];
            for (int k = B->col_ptr[colA]; k < B->col_ptr[colA + 1]; k++) {
                int colB = B->row_idx[k];
                double valB = B->values[k];
                #pragma omp atomic
                C[i][colB] += valA * valB;
            }
        }
    }
}

int main() {
    SparseMatrixCSR *A = read_sparse_matrix_csr("1.txt");
    SparseMatrixCSC *B = read_sparse_matrix_csc("2.txt");

    double **C = (double**)malloc(A->nrows * sizeof(double*));
    for (int i = 0; i < A->nrows; i++) {
        C[i] = (double*)calloc(B->ncols, sizeof(double));
    }

    multiply_sparse_matrices(A, B, C, A->nrows, B->ncols);

    printf("Resultado de la multiplicación de matrices dispersas:\n");
    for (int i = 0; i < A->nrows; i++) {
        for (int j = 0; j < B->ncols; j++) {
            if (C[i][j] != 0) {
                printf("%lf ", C[i][j]);
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }

    free(A->row_ptr);
    free(A->col_idx);
    free(A->values);
    free(A);

    free(B->col_ptr);
    free(B->row_idx);
    free(B->values);
    free(B);

    for (int i = 0; i < A->nrows; i++) {
        free(C[i]);
    }
    free(C);

    return 0;
}
