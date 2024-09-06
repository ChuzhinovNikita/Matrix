#include "../head_matrix.h"

int determinant(matrix_t *A, double *result) {
  int ret = OK;

  if (A == NULL || result == NULL || A->matrix == NULL) {
    ret = INCORRECT_MATRIX;
  } else if (A->columns != A->rows) {
    ret = CALCULATION_ERROR;
  } else if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else if (A->rows == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
  } else if (A->rows > 2) {
    int sign = 1;
    *result = 0;

    for (int i = 0; i < A->columns && ret == OK; i++) {
      double minor_det = 0;

      matrix_t *minor = minor_matrix(0, i, A);

      if (ret == OK) {
        ret = determinant(minor, &minor_det);
        if (ret == OK) {
          *result += sign * A->matrix[0][i] * minor_det;
          sign = -sign;
        }
        remove_matrix(minor);
        free(minor);
        minor = NULL;
      }
    }
  }

  return ret;
}