#include "../head_matrix.h"

int mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret = OK;

  if (is_matrix_valid(A) != OK || is_matrix_valid(B) != OK ||
      result == NULL) {
    ret = INCORRECT_MATRIX;
  } else if (A->columns != B->rows) {
    ret = CALCULATION_ERROR;
  } else if (create_matrix(A->rows, B->columns, result) != OK) {
    ret = INCORRECT_MATRIX;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        result->matrix[i][j] = 0;
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }

  return ret;
}