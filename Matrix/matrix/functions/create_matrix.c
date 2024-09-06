#include "../head_matrix.h"

int create_matrix(int rows, int columns, matrix_t *result) {
  int ret = OK;

  if (result == NULL) {
    ret = INCORRECT_MATRIX;
  } else if (rows < 1 || columns < 1) {
    ret = INCORRECT_MATRIX;
  } else {
    result->columns = columns;
    result->rows = rows;
    result->matrix = (double **)calloc(rows + rows * columns, sizeof(double));

    if (result->matrix != NULL) {
      double *start =
          (double *)((char *)result->matrix + rows * sizeof(double *));

      for (int i = 0; i < rows; i++) result->matrix[i] = start + i * columns;
    } else {
      ret = INCORRECT_MATRIX;
    }
  }

  return ret;
}