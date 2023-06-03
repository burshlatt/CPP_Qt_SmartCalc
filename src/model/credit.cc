#include "s21_calculator.h"

double annuity_credit(double sum, int term, int type, double percent,
                      double *month_pay, double *overpay) {
  if (type == 2) {
    term *= 12;
  }
  double percent_month = percent / (100 * percent);
  *month_pay = sum * percent_month / (1 - pow(1 + percent_month, -term));
  *overpay = *month_pay * term - sum;
  return sum + *overpay;
}

double differentiated_credit(double sum, int term, int type, double percent,
                             double *f_payment, double *l_payment,
                             double *overpay) {
  int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  time_t now;
  time(&now);
  struct tm *local = localtime(&now);
  int month = local->tm_mon;
  if (type == 2) {
    term *= 12;
  }
  double credit_body = sum / term;
  *overpay = (sum * (percent / 100) * days[month]) / 365;
  *f_payment = *overpay + credit_body;
  double sum_copy = sum;
  double percent_month = 0.0;
  for (int i = 0; i < term - 1; i++) {
    sum_copy -= credit_body;
    if (month == 11) {
      month = 0;
    } else {
      month++;
    }
    percent_month = (sum_copy * (percent / 100) * days[month]) / 365;
    *overpay += percent_month;
  }
  *l_payment = percent_month + credit_body;
  return sum + *overpay;
}
