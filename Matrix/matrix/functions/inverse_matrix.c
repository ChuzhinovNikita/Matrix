#include "../head_matrix.h"

int inverse_matrix(matrix_t *A, matrix_t *result) {
  int ret = 0;

  if (is_matrix_valid(A) != OK || result == NULL) {
    ret = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    ret = CALCULATION_ERROR;
  } else {
    double det = 0;
    if (determinant(A, &det) != 0 || fabs(det) < 1e-6) {
      ret = (fabs(det) < 1e-6) ? CALCULATION_ERROR : INCORRECT_MATRIX;
    } else {
      matrix_t complements = {0};
      if (calc_complements(A, &complements) != 0) {
        ret = INCORRECT_MATRIX;
      } else {
        matrix_t transposed_complements = {0};
        if (transpose(&complements, &transposed_complements) != 0) {
          remove_matrix(&complements);
          ret = INCORRECT_MATRIX;
        } else {
          if (create_matrix(A->rows, A->columns, result) != 0) {
            remove_matrix(&complements);
            remove_matrix(&transposed_complements);
            ret = INCORRECT_MATRIX;
          } else {
            for (int i = 0; i < A->rows; i++) {
              for (int j = 0; j < A->columns; j++) {
                result->matrix[i][j] =
                    transposed_complements.matrix[i][j] / det;
              }
            }
          }
          remove_matrix(&complements);
          remove_matrix(&transposed_complements);
        }
      }
    }
  }

  return ret;
}