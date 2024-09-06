#include <check.h>
#include <errno.h>

#include "head_matrix.h"

// create_matrix
START_TEST(test_create_matrix_1) {
  matrix_t A;
  int res = create_matrix(2, 3, &A);
  ck_assert_int_eq(A.rows, 2);
  ck_assert_int_eq(A.columns, 3);
  ck_assert_int_eq(res, 0);
  remove_matrix(&A);
}
END_TEST

START_TEST(test_create_matrix_2) {
  matrix_t A;
  int res = create_matrix(3, 3, &A);
  ck_assert_int_eq(A.rows, 3);
  ck_assert_int_eq(A.columns, 3);
  ck_assert_int_eq(res, 0);
  remove_matrix(&A);
}
END_TEST

START_TEST(test_create_matrix_3) {
  matrix_t A;
  int res = create_matrix(0, 3, &A);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_create_matrix_4) {
  matrix_t A;
  int res = create_matrix(3, -3, &A);
  ck_assert_int_eq(res, 1);
}
END_TEST

// eq_matrix
START_TEST(test_eq_matrix_1) {
  double count = 1.0;
  matrix_t A;
  matrix_t B;
  create_matrix(3, 3, &A);
  create_matrix(3, 3, &B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = count;
      B.matrix[i][j] = count;
      count = count + 1.0;
    }
  }
  int res = eq_matrix(&A, &B);
  ck_assert_int_eq(res, 1);
  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_2) {
  double count = 1.0;
  matrix_t A;
  matrix_t B;
  create_matrix(3, 1, &A);
  create_matrix(3, 1, &B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = count;
      B.matrix[i][j] = count;
      count = count + 1.0;
    }
  }
  int res = eq_matrix(&A, &B);
  ck_assert_int_eq(res, 1);
  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_4) {
  double count = 1.0;
  matrix_t A;
  matrix_t B;
  create_matrix(3, 3, &A);
  create_matrix(3, 3, &B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = count;
      B.matrix[i][j] = count + 1.0;
      count = count + 1.0;
    }
  }
  int res = eq_matrix(&A, &B);
  ck_assert_int_eq(res, 0);
  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_5) {
  matrix_t A;
  matrix_t B;
  create_matrix(3, 1, &A);
  create_matrix(3, 3, &B);
  int res = eq_matrix(&A, &B);
  ck_assert_int_eq(res, 0);
  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_6) {
  matrix_t A;
  matrix_t B;
  create_matrix(3, 1, &A);
  create_matrix(-1, 1, &B);
  int res = eq_matrix(&A, &B);
  ck_assert_int_eq(res, 0);
  remove_matrix(&A);
}
END_TEST

// sum_matrix
START_TEST(test_sum_matrix_1) {
  double count = 1.0;
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t D;
  create_matrix(3, 3, &A);
  create_matrix(3, 3, &B);
  create_matrix(3, 3, &C);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = count;
      B.matrix[i][j] = count;
      C.matrix[i][j] = A.matrix[i][j] + B.matrix[i][j];
      count = count + 1.0;
    }
  }

  int res = sum_matrix(&A, &B, &D);
  int res_eq = eq_matrix(&C, &D);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(res_eq, 1);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
  remove_matrix(&D);
}
END_TEST

START_TEST(test_sum_matrix_2) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  create_matrix(3, 1, &A);
  create_matrix(3, 3, &B);

  int res = sum_matrix(&A, &B, &C);
  ck_assert_int_eq(res, 2);
  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

// sub_matrix
START_TEST(test_sub_matrix_1) {
  double count = 1.0;
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t D;
  create_matrix(3, 3, &A);
  create_matrix(3, 3, &B);
  create_matrix(3, 3, &C);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = count;
      B.matrix[i][j] = count;
      C.matrix[i][j] = A.matrix[i][j] - B.matrix[i][j];
      count = count + 1.0;
    }
  }

  int res = sub_matrix(&A, &B, &D);
  int res_eq = eq_matrix(&C, &D);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(res_eq, 1);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
  remove_matrix(&D);
}
END_TEST

START_TEST(test_sub_matrix_2) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  create_matrix(3, 1, &A);
  create_matrix(3, 3, &B);

  int res = sub_matrix(&A, &B, &C);
  ck_assert_int_eq(res, 2);
  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_number_1) {
  double number = 2.0;
  double count = 1.0;
  matrix_t A;
  matrix_t B;
  matrix_t C;
  create_matrix(3, 3, &A);
  create_matrix(3, 3, &B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = count;
      B.matrix[i][j] = A.matrix[i][j] * number;
      count = count + 1.0;
    }
  }

  int res = mult_number(&A, number, &C);
  int res_eq = eq_matrix(&B, &C);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(res_eq, 1);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
}
END_TEST

START_TEST(test_mult_number_2) {
  double number = 2.0;

  int res = mult_number(NULL, number, NULL);
  ck_assert_int_eq(res, 1);
}
END_TEST

// mult_matrix
START_TEST(test_mult_matrix_1) {
  double count = 1.0;
  double count2 = 3.0;
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t D;
  create_matrix(1, 3, &A);
  create_matrix(3, 1, &B);
  create_matrix(1, 1, &C);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = count;
      B.matrix[j][i] = count2;
      count = count + 1.0;
      count2 = count2 - 1.0;
    }
  }
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      for (int k = 0; k < B.rows; k++) {
        C.matrix[i][j] += A.matrix[i][k] * B.matrix[k][j];
      }
    }
  }

  int res = mult_matrix(&A, &B, &D);
  int res_eq = eq_matrix(&C, &D);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(res_eq, 1);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
  remove_matrix(&D);
}
END_TEST

START_TEST(test_mult_matrix_2) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  create_matrix(1, 3, &A);
  create_matrix(4, 1, &B);
  create_matrix(1, 1, &C);

  int res = mult_matrix(&A, &B, &C);
  ck_assert_int_eq(res, 2);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
}
END_TEST

// transpose
START_TEST(test_transpose_1) {
  double count = 1.0;
  matrix_t A;
  matrix_t B;
  matrix_t C;
  create_matrix(2, 3, &A);
  create_matrix(3, 2, &B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = count;
      B.matrix[j][i] = count;
      count = count + 1.0;
    }
  }

  int res = transpose(&A, &C);
  int res_eq = eq_matrix(&B, &C);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(res_eq, 1);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
}
END_TEST

START_TEST(test_transpose_2) {
  int res = transpose(NULL, NULL);

  ck_assert_int_eq(res, 1);
}
END_TEST

// calc_complements
START_TEST(test_calc_complements_1) {
  matrix_t A;
  matrix_t B;
  create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  int res = calc_complements(&A, &B);
  ck_assert_int_eq(B.matrix[0][0], 0);
  ck_assert_int_eq(B.matrix[0][1], 10);
  ck_assert_int_eq(B.matrix[0][2], -20);
  ck_assert_int_eq(B.matrix[1][0], 4);
  ck_assert_int_eq(B.matrix[1][1], -14);
  ck_assert_int_eq(B.matrix[1][2], 8);
  ck_assert_int_eq(B.matrix[2][0], -8);
  ck_assert_int_eq(B.matrix[2][1], -2);
  ck_assert_int_eq(B.matrix[2][2], 4);
  ck_assert_int_eq(res, 0);
  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

START_TEST(test_calc_complements_2) {
  matrix_t A;
  matrix_t B;
  create_matrix(3, 3, &A);

  A.matrix[0][0] = 3;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 2;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 8;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 2;

  int res = calc_complements(&A, &B);
  ck_assert_int_eq(B.matrix[0][0], -12);
  ck_assert_int_eq(B.matrix[0][1], 20);
  ck_assert_int_eq(B.matrix[0][2], -2);
  ck_assert_int_eq(B.matrix[1][0], 0);
  ck_assert_int_eq(B.matrix[1][1], 0);
  ck_assert_int_eq(B.matrix[1][2], 0);
  ck_assert_int_eq(B.matrix[2][0], 12);
  ck_assert_int_eq(B.matrix[2][1], -20);
  ck_assert_int_eq(B.matrix[2][2], 2);
  ck_assert_int_eq(res, 0);
  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

START_TEST(test_calc_complements_3) {
  matrix_t A;
  matrix_t B;
  create_matrix(3, 1, &A);

  int res = calc_complements(&A, &B);
  ck_assert_int_eq(res, 2);
  remove_matrix(&A);
}
END_TEST

// inverse_matrix
START_TEST(inverse_1) {
  matrix_t A, C;
  create_matrix(3, 3, &A);
  create_matrix(3, 3, &C);
  C.matrix[0][0] = 1.0;
  C.matrix[0][1] = -1.0;
  C.matrix[0][2] = 1.0;
  C.matrix[1][0] = -38.0;
  C.matrix[1][1] = 41.0;
  C.matrix[1][2] = -34.0;
  C.matrix[2][0] = 27.0;
  C.matrix[2][1] = -29.0;
  C.matrix[2][2] = 24.0;
  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = 5.0;
  A.matrix[0][2] = 7.0;
  A.matrix[1][0] = 6.0;
  A.matrix[1][1] = 3.0;
  A.matrix[1][2] = 4.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = -2.0;
  A.matrix[2][2] = -3.0;
  matrix_t B;
  inverse_matrix(&A, &B);
  int res = eq_matrix(&B, &C);
  ck_assert_int_eq(res, 1);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
}
END_TEST

START_TEST(test_one_by_one) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = create_matrix(1, 1, &m);
  if (codec) {
    m.matrix[0][0] = 1431.12312331;
    int code = inverse_matrix(&m, &result);
    ck_assert_int_eq(result.matrix[0][0] == (1.0 / m.matrix[0][0]), 1);
    ck_assert_int_eq(code, OK);
    remove_matrix(&m);
    remove_matrix(&result);
  }
}
END_TEST

START_TEST(test_zero_det) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = create_matrix(1, 1, &m);
  if (codec) {
    int code = inverse_matrix(&m, &result);
    ck_assert_int_eq(code, CALCULATION_ERROR);
    remove_matrix(&m);
  }
}
END_TEST

START_TEST(test_incorrect) {
  matrix_t m = {0};
  matrix_t result = {0};
  int code = inverse_matrix(&m, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST


START_TEST(test_not_sqare) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = create_matrix(1, 4, &m);
  if (codec) {
    int code = inverse_matrix(&m, &result);
    ck_assert_int_eq(code, CALCULATION_ERROR);
    remove_matrix(&m);
  }
}
END_TEST

START_TEST(test_normal) {
  matrix_t m = {0};
  matrix_t expected = {0};
  int codec1, codec2;
  codec1 = create_matrix(3, 3, &m);
  if (codec1) codec2 = create_matrix(3, 3, &expected);

  if (codec1 && codec2) {
    m.matrix[0][0] = 2;
    m.matrix[0][1] = 5;
    m.matrix[0][2] = 7;

    m.matrix[1][0] = 6;
    m.matrix[1][1] = 3;
    m.matrix[1][2] = 4;

    m.matrix[2][0] = 5;
    m.matrix[2][1] = -2;
    m.matrix[2][2] = -3;

    expected.matrix[0][0] = 1;
    expected.matrix[0][1] = -1;
    expected.matrix[0][2] = 1;

    expected.matrix[1][0] = -38;
    expected.matrix[1][1] = 41;
    expected.matrix[1][2] = -34;

    expected.matrix[2][0] = 27;
    expected.matrix[2][1] = -29;
    expected.matrix[2][2] = 24;
    matrix_t result = {0};
    int code = inverse_matrix(&m, &result);

    ck_assert_int_eq(eq_matrix(&result, &expected), SUCCESS);
    ck_assert_int_eq(code, OK);

    remove_matrix(&m);
    remove_matrix(&result);
    remove_matrix(&expected);
  }
}
END_TEST

START_TEST(inverse) {
  const int size = 3;
  matrix_t m = {0};
  create_matrix(size, size, &m);

  m.matrix[0][0] = 2;
  m.matrix[0][1] = 5;
  m.matrix[0][2] = 7;
  m.matrix[1][0] = 6;
  m.matrix[1][1] = 3;
  m.matrix[1][2] = 4;
  m.matrix[2][0] = 5;
  m.matrix[2][1] = -2;
  m.matrix[2][2] = -3;

  matrix_t res = {0};
  inverse_matrix(&m, &res);

  matrix_t expected = {0};
  create_matrix(size, size, &expected);
  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = -1;
  expected.matrix[0][2] = 1;
  expected.matrix[1][0] = -38;
  expected.matrix[1][1] = 41;
  expected.matrix[1][2] = -34;
  expected.matrix[2][0] = 27;
  expected.matrix[2][1] = -29;
  expected.matrix[2][2] = 24;

  ck_assert_int_eq(eq_matrix(&expected, &res), SUCCESS);

  remove_matrix(&expected);
  remove_matrix(&res);
  remove_matrix(&m);
}
END_TEST
START_TEST(test_inverse_matrix_1) {
  matrix_t A;
  matrix_t B;
  create_matrix(3, 3, &A);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;

  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;

  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;

  int res = inverse_matrix(&A, &B);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(B.matrix[0][0], 1);
  ck_assert_int_eq(B.matrix[0][1], -1);
  ck_assert_int_eq(B.matrix[0][2], 1);
  ck_assert_int_eq(B.matrix[1][0], -38);
  ck_assert_int_eq(B.matrix[1][1], 41);
  ck_assert_int_eq(B.matrix[1][2], -34);
  ck_assert_int_eq(B.matrix[2][0], 27);
  ck_assert_int_eq(B.matrix[2][1], -29);
  ck_assert_int_eq(B.matrix[2][2], 24);
  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

START_TEST(test_inverse_matrix_2) {
  matrix_t A;
  matrix_t B;
  create_matrix(3, 3, &A);
  A.matrix[0][0] = 3;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 2;

  A.matrix[1][0] = 2;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 8;

  A.matrix[2][0] = 3;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 2;

  int res = inverse_matrix(&A, &B);
  ck_assert_int_eq(res, 2);
  remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_matrix_3) {
  matrix_t A;
  matrix_t B;
  create_matrix(3, 2, &A);

  int res = inverse_matrix(&A, &B);
  ck_assert_int_eq(res, 2);
  remove_matrix(&A);
}
END_TEST

int main() {
  Suite *s1 = suite_create("matrix: ");
  TCase *tc1_1 = tcase_create("matrix: ");
  SRunner *sr = srunner_create(s1);
  int result;
  suite_add_tcase(s1, tc1_1);

  //   create_matrix
  tcase_add_test(tc1_1, test_create_matrix_1);
  tcase_add_test(tc1_1, test_create_matrix_2);
  tcase_add_test(tc1_1, test_create_matrix_3);
  tcase_add_test(tc1_1, test_create_matrix_4);

  //   eq_matrix
  tcase_add_test(tc1_1, test_eq_matrix_1);
  tcase_add_test(tc1_1, test_eq_matrix_2);
  tcase_add_test(tc1_1, test_eq_matrix_4);
  tcase_add_test(tc1_1, test_eq_matrix_5);
  tcase_add_test(tc1_1, test_eq_matrix_6);

  // sum_matrix
  tcase_add_test(tc1_1, test_sum_matrix_1);
  tcase_add_test(tc1_1, test_sum_matrix_2);

  // sub_matrix
  tcase_add_test(tc1_1, test_sub_matrix_1);
  tcase_add_test(tc1_1, test_sub_matrix_2);

  // mult_number
  tcase_add_test(tc1_1, test_mult_number_1);
  tcase_add_test(tc1_1, test_mult_number_2);

  // mult_matrix
  tcase_add_test(tc1_1, test_mult_matrix_1);
  tcase_add_test(tc1_1, test_mult_matrix_2);

  // transpose
  tcase_add_test(tc1_1, test_transpose_1);
  tcase_add_test(tc1_1, test_transpose_2);

  // calc_complements
  tcase_add_test(tc1_1, test_calc_complements_1);
  tcase_add_test(tc1_1, test_calc_complements_2);
  tcase_add_test(tc1_1, test_calc_complements_3);


  // inverse_matrix
  tcase_add_test(tc1_1, test_inverse_matrix_1);
  tcase_add_test(tc1_1, test_inverse_matrix_2);
  tcase_add_test(tc1_1, test_inverse_matrix_3);
  tcase_add_test(tc1_1, inverse);
  tcase_add_test(tc1_1, inverse_1);

  tcase_add_test(tc1_1, test_normal);
  tcase_add_test(tc1_1, test_not_sqare);
  tcase_add_test(tc1_1, test_zero_det);
  tcase_add_test(tc1_1, test_incorrect);
  tcase_add_test(tc1_1, test_one_by_one);

  srunner_run_all(sr, CK_ENV);
  result = srunner_ntests_failed(sr);
  srunner_free(sr);
  return result == 0 ? 0 : 1;
}
