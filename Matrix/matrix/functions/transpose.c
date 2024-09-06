#include "../head_matrix.h"

int transpose(matrix_t *A, matrix_t *result) {
  int ret = OK;

  if (A == NULL || result == NULL || A->matrix == NULL) {
    ret = INCORRECT_MATRIX;
  } else if (A->columns < 1 || A->rows < 1) {
    ret = INCORRECT_MATRIX;
  } else {
    ret = create_matrix(A->columns, A->rows, result);

    for (int i = 0; i < A->rows && ret == OK; i++) {
      for (int j = 0; j < A->columns && ret == OK; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }

  return ret;
}