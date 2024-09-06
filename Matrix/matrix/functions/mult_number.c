#include "../head_matrix.h"

int mult_number(matrix_t *A, double number, matrix_t *result) {
  int ret = OK;

  if (is_matrix_valid(A) != OK || result == NULL) {
    ret = INCORRECT_MATRIX;
  } else {
    if (create_matrix(A->rows, A->columns, result) != OK) {
      ret = INCORRECT_MATRIX;
    } else {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    }
  }

  return ret;
}