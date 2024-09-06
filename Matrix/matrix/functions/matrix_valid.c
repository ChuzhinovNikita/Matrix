#include "../head_matrix.h"

int is_matrix_valid(matrix_t *A) {
  return (A != NULL && A->rows > 0 && A->columns > 0) ? OK : INCORRECT_MATRIX;
}