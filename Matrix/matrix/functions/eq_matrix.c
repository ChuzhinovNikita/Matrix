#include "../head_matrix.h"

int eq_matrix(matrix_t *A, matrix_t *B) {
  int ret = SUCCESS;

  if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL) {
    ret = FAILURE;
  } else if (A->columns < 1 || B->columns < 1 || A->rows < 1 || B->rows < 1) {
    ret = FAILURE;
  } else if (A->columns != B->columns || A->rows != B->rows) {
    ret = FAILURE;
  } else {
    for (int i = 0; i < A->rows && ret == SUCCESS; i++) {
      for (int j = 0; j < A->columns && ret == SUCCESS; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-6) ret = FAILURE;
      }
    }
  }

  return ret;
}