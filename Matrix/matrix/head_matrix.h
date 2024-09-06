#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

enum ERROR_CODES { OK, INCORRECT_MATRIX, CALCULATION_ERROR };

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int create_matrix(int rows, int columns,
                      matrix_t *result);  // Создание матриц (create_matrix)
void remove_matrix(matrix_t *A);  // Очистка матриц (remove_matrix)
int eq_matrix(matrix_t *A, matrix_t *B);  // Сравнение матриц (eq_matrix)

int sum_matrix(
    matrix_t *A, matrix_t *B,
    matrix_t *result);  // Сложение (sum_matrix) и вычитание матриц (sub_matrix)
int sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int mult_number(
    matrix_t *A, double number,
    matrix_t *result);  // Умножение матрицы на число (mult_number). Умножение
                        // двух матриц (mult_matrix)
int mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int transpose(matrix_t *A,
                  matrix_t *result);  // Транспонирование матрицы (transpose)

int calc_complements(
    matrix_t *A, matrix_t *result);  // Минор матрицы и матрица алгебраических
                                     // дополнений (calc_complements)

int determinant(matrix_t *A,
                    double *result);  // Определитель матрицы (determinant)

int inverse_matrix(matrix_t *A,
                       matrix_t *result);  // Обратная матрица (inverse_matrix)

matrix_t *minor_matrix(int a_row, int a_column, matrix_t *A);

int is_matrix_valid(matrix_t *A);

#endif