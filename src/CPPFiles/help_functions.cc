#include "s21_calculator.h"

void s21::calculator::SetOutput(int *i, int *index) {
  if (isdigit(output[i]) || output[i] == '.' || output[i] == 'x') {
    num = strtod(&output[i], &trash);
    if (output[i] == 'x') {
      num = xValue;
    }
    if (trash[0] == '-') {
      n_num++;
      if (n_num % 2 != 0) {
        num = -num;
      }
      n_num = 0;
    }
    i = trash - output;
    set_num(num_buffer, &top, num);
  }

  int is_negative = 0;
  char pi_chars[] = "3.141592";
  if ((str_[*i] == '-' && str_[*i - 1] == '(')) {
    *i += 1;
    is_negative = 1;
  }
  while ((str_[*i] >= '0' && str_[*i] <= '9') || str_[*i] == '.' || str_[*i] == 'x') {
    output[*index] = str_[*i];
    *index += 1;
    *i += 1;
  }
  if (str_[*i] == 'P') {
    for (int k = 0; k < 8; k++) {
      output[*index] = pi_chars[k];
      *index += 1;
    }
    *i += 2;
  }
  if (is_negative) {
    output[*index] = '-';
    *index += 1;
  }
  if ((str_[*i] < '0' || str_[*i] > '9') && str_[*i] != 'x') {
    if (str_[*i] != '(' && str_[*i] != ')') {
      if (str_[*i] != '.' && output[*index - 1] != ' ') {
        output[*index] = ' ';
        *index += 1;
      }
    }
  }
}

// int set_num(double *stack, int *top, double num) {
//   int error_status = 0;
//   if (*top != SIZE - 1) {
//     stack[++(*top)] = num;
//   }
//   return error_status;
// }

// double get_num(double *stack, int *top) {
//   double result = 0.0;
//   if (*top != -1) {
//     result = stack[(*top)--];
//   } else {
//     result = NAN;
//   }
//   return result;
// }

// int get_nums_func(double *num_buffer, int *top, double *x, double *y) {
//   int error_status = 0;
//   *x = get_num(num_buffer, top);
//   *y = get_num(num_buffer, top);
//   if (*x == NAN || *y == NAN) {
//     error_status = 1;
//   }
//   return error_status;
// }

// int is_func(struct Stack *stack) {
//   switch (peek(stack)) {
//     case 'c':
//     case 's':
//     case 't':
//     case 'C':
//     case 'S':
//     case 'T':
//     case '^':
//     case 'm':
//     case '~':
//     case 'L':
//     case 'l':
//       func = 1;
//       break;
//   }
//   return func;
// }

// void push_func(struct Stack *stack, char *string, int *index) {
//   if (string[*index] == 'c') {
//     push(stack, 'c');
//     *index += 3;
//   } else if (string[*index] == 's') {
//     if (string[*index + 1] == 'q') {
//       push(stack, '~');
//       *index += 4;
//     } else {
//       push(stack, 's');
//       *index += 3;
//     }
//   } else if (string[*index] == 't') {
//     push(stack, 't');
//     *index += 3;
//   } else if (string[*index] == 'a') {
//     if (string[*index + 1] == 'c') {
//       push(stack, 'C');
//       *index += 4;
//     } else if (string[*index + 1] == 's') {
//       push(stack, 'S');
//       *index += 4;
//     } else if (string[*index + 1] == 't') {
//       push(stack, 'T');
//       *index += 4;
//     } else if (string[*index + 1] == 'b') {
//       push(stack, '|');
//       *index += 3;
//     }
//   } else if (string[*index] == 'l') {
//     if (string[*index + 1] == 'n') {
//       push(stack, 'l');
//       *index += 2;
//     } else {
//       push(stack, 'L');
//       *index += 3;
//     }
//   } else if (string[*index] == '^') {
//     push(stack, '^');
//   }
//   if (string[*index] == '(') {
//     push(stack, '(');
//   }
// }

// void set_space(char *output, int *index) {
//   if (output[*index - 1] != ' ') {
//     output[*index] = ' ';
//     *index += 1;
//   }
// }

// void set_in_output(struct Stack *stack, char *output, int *index) {
//   output[*index] = pop(stack);
//   *index += 1;
// }

// void logic_actions(struct Stack *stack, char *output, int *index) {
//   set_space(output, index);
//   set_in_output(stack, output, index);
//   set_space(output, index);
// }

// int do_pop(struct Stack *stack, char *output, int *index, int variant) {
//   int error_status = 0;
//   if (variant == 1) {
//     while (!is_empty(stack) && peek(stack) != '(' && peek(stack) != '\0') {
//       logic_actions(stack, output, index);
//     }
//   } else if (variant == 2) {
//     while (!is_empty(stack)) {
//       logic_actions(stack, output, index);
//     }
//   } else if (variant == 3) {
//     while (peek(stack) != '(' && peek(stack) != '\0') {
//       if (is_empty(stack)) {
//         error_status = 1;
//         break;
//       }
//       logic_actions(stack, output, index);
//     }
//   } else if (variant == 4) {
//     while (is_func(stack)) {
//       logic_actions(stack, output, index);
//     }
//   } else if (variant == 5) {
//     while (!is_empty(stack) && peek(stack) != '-' && peek(stack) != '+' &&
//            peek(stack) != '(' && peek(stack) != '\0') {
//       logic_actions(stack, output, index);
//     }
//   }
//   return error_status;
// }

// double convert_to_days(int time_contrib, int type_of_time) {
//   int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
//   time_t now;
//   time(&now);
//   struct tm *local = localtime(&now);
//   int month = local->tm_mon;
//   double time_copy = 0;
//   if (type_of_time == 1) {
//     time_copy = time_contrib;
//   } else if (type_of_time == 3) {
//     time_contrib *= 12;
//   }
//   if (type_of_time != 1) {
//     for (int i = 0; i < time_contrib; i++) {
//       time_copy += days[month];
//       if (month == 11) {
//         month = 0;
//       } else {
//         month++;
//       }
//     }
//   }
//   return time_copy;
// }

// int convert_to_months(int time_contrib, int type_of_time) {
//   int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
//   time_t now;
//   time(&now);
//   struct tm *local = localtime(&now);
//   int month = local->tm_mon;
//   double time_copy = 0;
//   if (type_of_time == 1) {
//     while (time_contrib >= days[month]) {
//       time_contrib -= days[month];
//       if (month == 11) {
//         month = 0;
//       } else {
//         month++;
//       }
//       time_copy++;
//     }
//   } else if (type_of_time == 2) {
//     time_copy = time_contrib;
//   } else if (type_of_time == 3) {
//     time_copy = time_contrib * 12;
//   }
//   return time_copy;
// }

// double add_start_sum(double sum, int time, int type) {
//   double sum_result = 0.0;
//   if (type == 2) {
//     time = (int)(time / 2);
//   } else if (type == 3) {
//     time = (int)(time / 3);
//   } else if (type == 4) {
//     time = (int)(time / 6);
//   } else if (type == 5) {
//     time = (int)(time / 12);
//   }
//   for (int i = 0; i < time; i++) {
//     sum_result += sum;
//   }
//   return sum_result;
// }

// int check_period(int capitalization, int period, double *time_copy) {
//   int n = 0;
//   if (!capitalization) {
//     if (period == 1 || period == 7) {
//       n = 365;
//     } else if (period == 2) {
//       n = 52;
//       *time_copy = floor(*time_copy / 7);
//     } else if (period == 3) {
//       n = 12;
//       *time_copy = floor(*time_copy / 30.5);
//     } else if (period == 4) {
//       n = 4;
//       *time_copy = floor(*time_copy / 91.25);
//     } else if (period == 5) {
//       n = 2;
//       *time_copy = floor(*time_copy / 182.5);
//     } else if (period == 6) {
//       n = 1;
//       *time_copy = floor(*time_copy / 365);
//     }
//   } else {
//     if (period == 1) {
//       n = 365;
//     } else if (period == 2) {
//       n = 52;
//     } else if (period == 3) {
//       n = 12;
//     } else if (period == 4) {
//       n = 4;
//     } else if (period == 5) {
//       n = 2;
//     } else if (period == 6 || period == 7) {
//       n = 1;
//     }
//   }
//   return n;
// }

// char *current_date() {
//   char *date = malloc(10 * sizeof(char));
//   int day, month, year;
//   time_t now;
//   time(&now);
//   struct tm *local = localtime(&now);
//   day = local->tm_mday;
//   month = local->tm_mon + 1;
//   year = local->tm_year + 1900;
//   sprintf(date, "%02d/%02d/%d", day, month, year);
//   return date;
// }

// char *end_date(char *date, int time_contrib, int type_of_time) {
//   int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
//   int count_days = convert_to_days(time_contrib, type_of_time);
//   char *date_result = malloc(10 * sizeof(char));
//   int date_arr[3] = {0, 0, 0};
//   char *trash;
//   int j = 0;
//   for (int i = 0; date[i]; i++) {
//     if (isdigit(date[i])) {
//       date_arr[j] = strtod(&date[i], &trash);
//       i = trash - date;
//       j++;
//     }
//   }
//   for (int i = 0; i < count_days; i++) {
//     date_arr[0] += 1;
//     if (date_arr[DAY] > days[date_arr[1] - 1]) {
//       date_arr[DAY] = 1;
//       date_arr[MONTH] += 1;
//     }
//     if (date_arr[MONTH] > 12) {
//       date_arr[MONTH] = 1;
//       date_arr[YEAR] += 1;
//     }
//   }
//   sprintf(date_result, "%02d/%02d/%d", date_arr[0], date_arr[1], date_arr[2]);
//   return date_result;
// }

// void do_correct_date(char *date_first, char *date_second) {
//   for (int i = 0; i < 10; i++) {
//     if (date_first[i] == '.') {
//       date_first[i] = '/';
//     }
//     if (date_second[i] == '.') {
//       date_second[i] = '/';
//     }
//   }
// }

// int days_in_month(int month, int year) {
//   int days[] = {
//       31, 28 + (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)),
//       31, 30,
//       31, 30,
//       31, 31,
//       30, 31,
//       30, 31};
//   return days[month - 1];
// }

// int date_difference(char *date_first, char *date_second) {
//   do_correct_date(date_first, date_second);
//   int first_array[3] = {0, 0, 0};
//   int second_array[3] = {0, 0, 0};
//   sscanf(date_first, "%d/%d/%d", &first_array[DAY], &first_array[MONTH],
//          &first_array[YEAR]);
//   sscanf(date_second, "%d/%d/%d", &second_array[DAY], &second_array[MONTH],
//          &second_array[YEAR]);
//   int month_diff = (first_array[YEAR] - second_array[YEAR]) * 12 +
//                    first_array[MONTH] - second_array[MONTH];
//   int day_diff = first_array[DAY] - second_array[DAY];
//   if (day_diff < 0) {
//     month_diff--;
//     day_diff += days_in_month(second_array[MONTH], second_array[YEAR]);
//   }
//   return month_diff;
// }

// void free_array(char *date) { free(date); }
