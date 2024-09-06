#include "../head_matrix.h"

int calc_complements(matrix_t *A, matrix_t *result) {
  int ret = OK;

  if (A == NULL || result == NULL || A->matrix == NULL) {
    ret = INCORRECT_MATRIX;
  } else if (A->columns < 1 || A->rows < 1) {
    ret = INCORRECT_MATRIX;
  } else if (A->rows == 1 || A->columns == 1 || A->rows != A->columns) {
    ret = CALCULATION_ERROR;
  } else {
    ret = create_matrix(A->rows, A->columns, result);
  }

  if (ret == OK && result != NULL) {
    for (int i = 0; i < A->rows && ret == OK; i++) {
      int sign = i % 2 == 0 ? 1 : -1;
      for (int j = 0; j < A->columns && ret == OK; j++) {
        matrix_t *minor = minor_matrix(i, j, A);
        if (minor == NULL) {
          ret = INCORRECT_MATRIX;
        } else {
          double det = 0;
          ret = determinant(minor, &det);
          if (!isfinite(det)) ret = CALCULATION_ERROR;
          if (ret == OK) {
            result->matrix[i][j] = sign * det;
            sign = -sign;
          }
          remove_matrix(minor);
          free(minor);
          minor = NULL;
        }
      }
    }
  }

  return ret;
}

matrix_t *minor_matrix(int a_row, int a_column, matrix_t *A) {
  matrix_t *minor = calloc(1, sizeof(matrix_t));

  if (A == NULL || A->matrix == NULL) minor = NULL;

  if (minor != NULL) {
    if (create_matrix(A->rows - 1, A->columns - 1, minor) == OK) {
      for (int i = 0, minor_row = 0; i < A->rows; i++) {
        if (i != a_row) {
          for (int j = 0, minor_column = 0; j < A->columns; j++) {
            if (j != a_column) {
              minor->matrix[minor_row][minor_column] = A->matrix[i][j];
              minor_column++;
            }
          }
          minor_row++;
        }
      }
    }
  }

  return minor;
}