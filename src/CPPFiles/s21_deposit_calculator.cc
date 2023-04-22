#include "s21_calculator.h"

void deposit_calculator(double sum, int time_contrib, int type_of_time,
                        double percent, double tax_rate, int period,
                        int capitalization, double *res_percent,
                        double *tax_rate_res, double *sum_with_tax,
                        double *sum_res) {
  double time_copy = convert_to_days(time_contrib, type_of_time);
  int n = check_period(capitalization, period, &time_copy);
  if (!capitalization) {
    *sum_res = sum;
    *res_percent = (sum * (percent / 100) / n) * time_copy;
  } else {
    *sum_res = sum * pow(1 + (percent / 100) / n, time_copy / 365 * n);
    *res_percent = *sum_res - sum;
  }
  *tax_rate_res = *res_percent - 1000000 * (7.5 / 100);
  if (*tax_rate_res > 0) {
    *tax_rate_res *= tax_rate / 100;
  } else {
    *tax_rate_res = 0;
  }
  *sum_with_tax = *res_percent - *tax_rate_res;
}
