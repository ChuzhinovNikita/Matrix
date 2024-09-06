#include "../head_matrix.h"

int sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret = OK;

  if (is_matrix_valid(A) != OK || is_matrix_valid(B) != OK ||
      result == NULL) {
    ret = INCORRECT_MATRIX;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    ret = CALCULATION_ERROR;
  } else {
    if (create_matrix(A->rows, A->columns, result) != OK) {
      ret = INCORRECT_MATRIX;
    } else {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    }
  }

  return ret;
}