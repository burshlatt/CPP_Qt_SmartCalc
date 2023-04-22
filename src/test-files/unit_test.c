#include "../CFiles/s21_calculator.h"
#include <check.h>

int error = 0;

START_TEST(number_test) {
  double result = 0;
  // test 1
  char string_1[255] = "12.3+4";
  result = polish_notation(string_1, 0, 0, &error);
  ck_assert_double_eq_tol(result, 16.3, 1e-7);
  // test 2
  char string_2[255] = "(12)";
  result = polish_notation(string_2, 0, 0, &error);
  ck_assert_double_eq_tol(result, 12, 1e-7);
}

// plus test
START_TEST(plus_test) {
  double result = 0;
  // test 1
  char string_1[255] = "(-12.3)+4";
  result = polish_notation(string_1, 0, 0, &error);
  ck_assert_double_eq_tol(result, -8.3, 1e-7);
  // test 2
  char string_2[255] = "(12)+(-12.00006)";
  result = polish_notation(string_2, 0, 0, &error);
  ck_assert_double_eq_tol(result, -0.00006, 1e-7);
  // test 8
  char string_8[255] = "1.2+1.2+2.4+4.8";
  result = polish_notation(string_8, 0, 0, &error);
  ck_assert_double_eq_tol(result, 9.6, 1e-7);
}

// sub test
START_TEST(sub_test) {
  double result = 0;
  // test 1
  char string_1[255] = "(-12.3)-4";
  result = polish_notation(string_1, 0, 0, &error);
  ck_assert_double_eq_tol(result, -16.3, 1e-7);
  // test 2
  char string_2[255] = "(12)-(-12.00006)";
  result = polish_notation(string_2, 0, 0, &error);
  ck_assert_double_eq_tol(result, 24.00006, 1e-7);
  // test 5
  char string_5[255] = "(-1.12)";
  result = polish_notation(string_5, 0, 0, &error);
  ck_assert_double_eq_tol(result, -1.12, 1e-7);
  // test 6
  char string_6[255] = "(-(-(-10)))-(-(-10))";
  result = polish_notation(string_6, 0, 0, &error);
  ck_assert_double_eq_tol(result, -20, 1e-7);
  // test 8
  char string_8[255] = "(-1.2)-1.2-2.4-4.8";
  result = polish_notation(string_8, 0, 0, &error);
  ck_assert_double_eq_tol(result, -9.6, 1e-7);
}

// mul test
START_TEST(mul_test) {
  double result = 0;
  // test 1
  char string_1[255] = "(-1.3)*4";
  result = polish_notation(string_1, 0, 0, &error);
  ck_assert_double_eq_tol(result, -5.2, 1e-7);
  // test 2
  char string_2[255] = "(12)*(-1.0006)";
  result = polish_notation(string_2, 0, 0, &error);
  ck_assert_double_eq_tol(result, -12.0072, 1e-7);
  // test 6
  char string_6[255] = "(-(-(-10)))*(-(-10))";
  result = polish_notation(string_6, 0, 0, &error);
  ck_assert_double_eq_tol(result, -100, 1e-7);
}

// div test
START_TEST(div_test) {
  double result = 0;
  // test 1
  char string_1[255] = "(-1.3)/4";
  result = polish_notation(string_1, 0, 0, &error);
  ck_assert_double_eq_tol(result, -0.325, 1e-7);
  // test 2
  char string_2[255] = "(12)/(-1.0006)";
  result = polish_notation(string_2, 0, 0, &error);
  ck_assert_double_eq_tol(result, -11.9928043, 1e-7);
  // test 6
  char string_6[255] = "(-(-(-10)))/(-(-10))";
  result = polish_notation(string_6, 0, 0, &error);
  ck_assert_double_eq_tol(result, -1, 1e-7);
  // test 9
  char string_9[255] = "2/0";
  result = polish_notation(string_9, 0, 0, &error);
  ck_assert_double_eq_tol(result, 0.000000, 1e-7);
  ck_assert_double_eq(error, 2);
}

// mod test
START_TEST(mod_test) {
  double result = 0;
  // test 1
  char string_1[] = "(-1.3)mod4";
  result = polish_notation(string_1, 0, 0, &error);
  ck_assert_double_eq_tol(result, -1.3, 1e-7);
  // test 2
  char string_2[255] = "(12)mod(-1.0006)";
  result = polish_notation(string_2, 0, 0, &error);
  ck_assert_double_eq_tol(result, 0.9934000000000007, 1e-7);
  // test 3
  char string_3[255] = "(12.2)mod12.02";
  result = polish_notation(string_3, 0, 0, &error);
  ck_assert_double_eq_tol(result, 0.17999999999999972, 1e-7);
  // test 6
  char string_6[255] = "(-(-(-10)))mod(-(-10))";
  result = polish_notation(string_6, 0, 0, &error);
  ck_assert_double_eq_tol(result, 0, 1e-7);
}

// deg test
START_TEST(deg_test) {
  double result = 0;
  // test 1
  char string_1[255] = "(-1.3)^4";
  result = polish_notation(string_1, 0, 0, &error);
  ck_assert_double_eq_tol(result, 2.8561, 1e-7);
  // test 2
  char string_2[255] = "(12)^(-1.0006)";
  result = polish_notation(string_2, 0, 0, &error);
  ck_assert_double_eq_tol(result, 0.08320918057, 1e-7);
  // test 3
  char string_3[255] = "(12.2)^2.02";
  result = polish_notation(string_3, 0, 0, &error);
  ck_assert_double_eq_tol(result, 156.475683751, 1e-7);
  // test 6
  char string_6[255] = "(-(-(-10)))^(-(-1))";
  result = polish_notation(string_6, 0, 0, &error);
  ck_assert_double_eq_tol(result, -10, 1e-7);
  // test 9
  char string_9[255] = "2^2^3";
  result = polish_notation(string_9, 0, 0, &error);
  ck_assert_double_eq_tol(result, 256, 1e-7);
}

// sqrt test
START_TEST(sqrt_test) {
  double result = 0;
  // test 1
  char string_1[255] = "sqrt(4)";
  result = polish_notation(string_1, 0, 0, &error);
  ck_assert_double_eq_tol(result, 2, 1e-7);
  // test 2
  char string_2[255] = "sqrt(-4)";
  result = polish_notation(string_2, 0, 0, &error);
  ck_assert_double_nan(result);
  // test 3
  char string_3[255] = "(-1)*sqrt(4)";
  result = polish_notation(string_3, 0, 0, &error);
  ck_assert_double_eq_tol(result, -2, 1e-7);
  // test 6
  char string_6[255] = "sqrt((((((4))))))";
  result = polish_notation(string_6, 0, 0, &error);
  ck_assert_double_eq_tol(result, 2, 1e-7);
}

// sin test
START_TEST(sin_test) {
  double result = 0;
  // test 1
  char string_1[255] = "sin(3.14*2)";
  result = polish_notation(string_1, 0, 0, &error);
  ck_assert_double_eq_tol(result, 0.1093873, 1e-7);
  // test 2
  char string_2[255] = "sin(1)";
  result = polish_notation(string_2, 0, 0, &error);
  ck_assert_double_eq_tol(result, 0.0174524, 1e-7);
  // test 3
  char string_3[255] = "(-1)*sin(1)";
  result = polish_notation(string_3, 0, 0, &error);
  ck_assert_double_eq_tol(result, -0.0174524, 1e-7);
  // test 6
  char string_6[255] = "sin((((((4))))))";
  result = polish_notation(string_6, 0, 0, &error);
  ck_assert_double_eq_tol(result, 0.0697565, 1e-7);
}

// cos test
START_TEST(cos_test) {
  double result = 0;
  // test 1
  char string_1[255] = "cos(3.14*2)";
  result = polish_notation(string_1, 0, 0, &error);
  ck_assert_double_eq_tol(result, 0.9939992, 1e-7);
  // test 2
  char string_2[255] = "cos(1)";
  result = polish_notation(string_2, 0, 0, &error);
  ck_assert_double_eq_tol(result, 0.9998477, 1e-7);
  // test 3
  char string_3[255] = "(-1)*cos(1)";
  result = polish_notation(string_3, 0, 0, &error);
  ck_assert_double_eq_tol(result, -0.9998477, 1e-7);
  // test 6
  char string_6[255] = "cos((((((4))))))";
  result = polish_notation(string_6, 0, 0, &error);
  ck_assert_double_eq_tol(result, 0.9975641, 1e-7);
}

// tan test
START_TEST(tan_test) {
  double result = 0;
  // test 1
  char string_1[255] = "tan(3.14*2)";
  result = polish_notation(string_1, 0, 0, &error);
  ck_assert_double_eq_tol(result, 0.1100477, 1e-7);
  // test 2
  char string_2[255] = "tan(1)";
  result = polish_notation(string_2, 0, 0, &error);
  ck_assert_double_eq_tol(result, 0.0174551, 1e-7);
  // test 3
  char string_3[255] = "(-1)*tan(1)";
  result = polish_notation(string_3, 0, 0, &error);
  ck_assert_double_eq_tol(result, -0.0174551, 1e-7);
  // test 6
  char string_6[255] = "tan((((((4))))))";
  result = polish_notation(string_6, 0, 0, &error);
  ck_assert_double_eq_tol(result, 0.0699268, 1e-7);
}

// asin test
START_TEST(asin_test) {
  double result = 0;
  // test 1
  char string_1[255] = "asin(3.14*2)";
  result = polish_notation(string_1, 0, 0, &error);
  ck_assert_double_eq_tol(result, 0.1098273, 1e-6);
  // test 2
  char string_2[255] = "asin(0.9)";
  result = polish_notation(string_2, 0, 0, &error);
  ck_assert_double_eq_tol(result, 0.0157086, 1e-6);
  // test 3
  char string_3[255] = "(-1)*asin(0.9)";
  result = polish_notation(string_3, 0, 0, &error);
  ck_assert_double_eq_tol(result, -0.0157086, 1e-6);
  // test 6
  char string_6[255] = "asin((((((-0.0001))))))";
  result = polish_notation(string_6, 0, 0, &error);
  ck_assert_double_eq_tol(result, -0.0000017, 1e-6);
}

// acos test
START_TEST(acos_test) {
  double result = 0;
  // test 1
  char string_1[255] = "acos(3.14*2)";
  result = polish_notation(string_1, 0, 0, &error);
  ck_assert_double_eq_tol(result, 1.4609690, 1e-6);
  // test 2
  char string_2[255] = "acos(0.9)";
  result = polish_notation(string_2, 0, 0, &error);
  ck_assert_double_eq_tol(result, 1.5550877, 1e-6);
  // test 3
  char string_3[255] = "(-1)*acos(0.9)";
  result = polish_notation(string_3, 0, 0, &error);
  ck_assert_double_eq_tol(result, -1.5550877, 1e-6);
  // test 6
  char string_6[255] = "acos((((((-0.0001))))))";
  result = polish_notation(string_6, 0, 0, &error);
  ck_assert_double_eq_tol(result, 1.5707981, 1e-6);
}

// atan test
START_TEST(atan_test) {
  double result = 0;
  // test 1
  char string_1[255] = "atan(3.14*2)";
  result = polish_notation(string_1, 0, 0, &error);
  ck_assert_double_eq_tol(result, 0.1091709, 1e-6);
  // test 2
  char string_2[255] = "atan(0.9)";
  result = polish_notation(string_2, 0, 0, &error);
  ck_assert_double_eq_tol(result, 0.0157067, 1e-6);
  // test 3
  char string_3[255] = "(-1)*atan(0.9)";
  result = polish_notation(string_3, 0, 0, &error);
  ck_assert_double_eq_tol(result, -0.0157067, 1e-6);
  // test 6
  char string_6[255] = "atan((((((-0.0001))))))";
  result = polish_notation(string_6, 0, 0, &error);
  ck_assert_double_eq_tol(result, -0.0000017, 1e-6);
}

// ln test
START_TEST(ln_test) {
  double result = 0;
  // test 1
  char string_1[255] = "ln(3.14*2)";
  result = polish_notation(string_1, 0, 0, &error);
  ck_assert_double_eq_tol(result, 1.8373700, 1e-6);
  // test 2
  char string_2[255] = "ln(0.9)";
  result = polish_notation(string_2, 0, 0, &error);
  ck_assert_double_eq_tol(result, -0.1053605, 1e-6);
  // test 3
  char string_3[255] = "(-1)*ln(0.9)";
  result = polish_notation(string_3, 0, 0, &error);
  ck_assert_double_eq_tol(result, 0.1053605, 1e-6);
  // test 6
  char string_6[255] = "ln((((((-0.0001))))))";
  result = polish_notation(string_6, 0, 0, &error);
  ck_assert_double_nan(result);
}

// log test
START_TEST(log_test) {
  double result = 0;
  // test 1
  char string_1[255] = "log(3.14*2)";
  result = polish_notation(string_1, 0, 0, &error);
  ck_assert_double_eq_tol(result, 0.7979596, 1e-6);
  // test 2
  char string_2[255] = "log(0.9)";
  result = polish_notation(string_2, 0, 0, &error);
  ck_assert_double_eq_tol(result, -0.0457575, 1e-6);
  // test 3
  char string_3[255] = "(-1)*log(0.9)";
  result = polish_notation(string_3, 0, 0, &error);
  ck_assert_double_eq_tol(result, 0.0457575, 1e-6);
  // test 6
  char string_6[255] = "log((((((-0.0001))))))";
  result = polish_notation(string_6, 0, 0, &error);
  ck_assert_double_nan(result);
}

//  test
START_TEST(algebraic_equation_test) {
  double result = 0;
  // test 1
  char string_1[255] = "sin(1.0009-12.53)*cos(1.25*2^3)";
  result = polish_notation(string_1, 0, 0, &error);
  ck_assert_double_eq_tol(result, -0.1968292, 1e-6);
  // test 2
  char string_2[255] = "log(15.3)*log(-10)+15-1*15/14";
  result = polish_notation(string_2, 0, 0, &error);
  ck_assert_double_nan(result);
  // test 3
  char string_3[255] = "2^2^3*3^2^3";
  result = polish_notation(string_3, 0, 0, &error);
  ck_assert_double_eq_tol(result, 1679616.000000, 1e-6);
  // test 6
  char string_6[255] =
      "sin(30)+cos(30)*tan(30)/acos(0.15)^asin(0.15)+(-1)*atan(0.15)";
  result = polish_notation(string_6, 0, 0, &error);
  ck_assert_double_eq_tol(result, 0.9967934, 1e-6);
  // test 7
  char string_7[255] = "17mod13mod5";
  result = polish_notation(string_7, 0, 0, &error);
  ck_assert_double_eq_tol(result, 4, 1e-6);
}

START_TEST(credit_test) {
  double month_pay = 0.0;
  double overpay = 0.0;
  double sum = annuity_credit(1000000, 1, 2, 13, &month_pay, &overpay);
  ck_assert_double_eq_tol(sum, 1066185.46, 1e-2);
  ck_assert_double_eq_tol(month_pay, 88848.79, 1e-2);
  ck_assert_double_eq_tol(overpay, 66185.46, 1e-2);

  double f_payment = 0.0;
  double l_payment = 0.0;
  overpay = 0.0;
  sum = differentiated_credit(1000000, 1, 2, 13, &f_payment, &l_payment,
                              &overpay);
  ck_assert_double_eq_tol(sum, 1069926.94, 1e-2);
  ck_assert_double_eq_tol(f_payment, 93305.94, 1e-2);
  ck_assert_double_eq_tol(l_payment, 84253.42, 1e-2);
  ck_assert_double_eq_tol(overpay, 69926.94, 1e-2);
}

START_TEST(deposit_test) {
  double sum_res = 0.0;
  double res_percent = 0.0;
  double tax_rate_res = 0.0;
  double sum_with_tax = 0.0;
  deposit_calculator(1000000, 1, 3, 10, 13, 3, 0, &res_percent, &tax_rate_res,
                     &sum_with_tax, &sum_res);
  ck_assert_double_eq_tol(sum_res, 1000000.00, 1e-2);
  ck_assert_double_eq_tol(res_percent, 91666.67, 1e-2);
  ck_assert_double_eq_tol(tax_rate_res, 2166.67, 1e-2);
  ck_assert_double_eq_tol(sum_with_tax, 89500.00, 1e-2);

  sum_res = 0.0;
  res_percent = 0.0;
  tax_rate_res = 0.0;
  sum_with_tax = 0.0;
  deposit_calculator(1000000, 1, 3, 10, 13, 3, 1, &res_percent, &tax_rate_res,
                     &sum_with_tax, &sum_res);
  ck_assert_double_eq_tol(sum_res, 1104713.07, 1e-2);
  ck_assert_double_eq_tol(res_percent, 104713.07, 1e-2);
  ck_assert_double_eq_tol(tax_rate_res, 3862.70, 1e-2);
  ck_assert_double_eq_tol(sum_with_tax, 100850.37, 1e-2);

  sum_res = 0.0;
  res_percent = 0.0;
  tax_rate_res = 0.0;
  sum_with_tax = 0.0;
  deposit_calculator(1000000, 1, 2, 10, 13, 3, 1, &res_percent, &tax_rate_res,
                     &sum_with_tax, &sum_res);
  ck_assert_double_eq_tol(sum_res, 1007668.70, 1e-2);
  ck_assert_double_eq_tol(res_percent, 7668.70, 1e-2);
  ck_assert_double_eq_tol(tax_rate_res, 0.00, 1e-2);
  ck_assert_double_eq_tol(sum_with_tax, 7668.70, 1e-2);
}

START_TEST(other_test) {
  int error = 0;
  double result =
      polish_notation("sqrt(cos(x))*cos(200*x)+sqrt(abs(x))-3.1415/"
                      "4*(4-x^2)^0.01+sin(x)+tan(x)+acos(x)+asin(x)+atan(x)",
                      1, 0, &error);
  ck_assert_double_eq_tol(result, 1.774458, 1e-6);

  error = 0;
  result = polish_notation("1+(-2", 1, 0, &error);
  ck_assert_double_eq(error, 1);
}

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);

  int failed = 0;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, ln_test);
  tcase_add_test(tc1_1, sub_test);
  tcase_add_test(tc1_1, mul_test);
  tcase_add_test(tc1_1, div_test);
  tcase_add_test(tc1_1, mod_test);
  tcase_add_test(tc1_1, deg_test);
  tcase_add_test(tc1_1, sin_test);
  tcase_add_test(tc1_1, cos_test);
  tcase_add_test(tc1_1, tan_test);
  tcase_add_test(tc1_1, log_test);
  tcase_add_test(tc1_1, plus_test);
  tcase_add_test(tc1_1, sqrt_test);
  tcase_add_test(tc1_1, asin_test);
  tcase_add_test(tc1_1, acos_test);
  tcase_add_test(tc1_1, atan_test);
  tcase_add_test(tc1_1, other_test);
  tcase_add_test(tc1_1, credit_test);
  tcase_add_test(tc1_1, number_test);
  tcase_add_test(tc1_1, deposit_test);
  tcase_add_test(tc1_1, algebraic_equation_test);

  srunner_run_all(sr, CK_ENV);
  failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
