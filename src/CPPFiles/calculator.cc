#include "calculator.h"

// double polish_notation(char *str, int is_graph, double xValue, int *error_flag) {
//   struct Stack *stack = create_stack(SIZE);
//   int index = 0;
//   double result = 0.0;
//   int count_of_left_bracket = 0;
//   int count_of_right_bracket = 0;
//   char output[255] = {'\0'};
//   for (int i = 0; str[i] != '\0'; i++) {
//     if (str[i] == '(') {
//       count_of_left_bracket++;
//     }
//     if (str[i] == ')') {
//       count_of_right_bracket++;
//     }
//   }
//   for (int i = 0; i < (int)strlen(str) + 1 && index < 255; i++) {
//     set_nums_output(str, &i, output, &index);
//     if (*error_flag == 0) {
//       switch (str[i]) {
//       case '^':
//       case 'c':
//       case 's':
//       case 't':
//       case 'a':
//       case 'l':
//       case '(':
//         push_func(stack, str, &i);
//         break;
//       case 'm':
//         do_pop(stack, output, &index, 1);
//         push(stack, 'm');
//         break;
//       case '*':
//         do_pop(stack, output, &index, 5);
//         push(stack, '*');
//         break;
//       case '/':
//         do_pop(stack, output, &index, 5);
//         push(stack, '/');
//         break;
//       case '+':
//         do_pop(stack, output, &index, 1);
//         push(stack, '+');
//         break;
//       case '-':
//         if (str[i - 1] != '(') {
//           do_pop(stack, output, &index, 1);
//           push(stack, '-');
//         }
//         break;
//       case ')':
//         *error_flag = do_pop(stack, output, &index, 3);
//         if (*error_flag == 0) {
//           pop(stack);
//           do_pop(stack, output, &index, 4);
//         }
//         break;
//       case '\0':
//         do_pop(stack, output, &index, 2);
//         break;
//       }
//     }
//   }
//   delete_stack(stack);
//   if (count_of_left_bracket != count_of_right_bracket) {
//     *error_flag = 1;
//   }
//   if (!(*error_flag)) {
//     result = arithmetic_calculations(output, is_graph, xValue, error_flag);
//   }
//   return !(*error_flag) ? result : 0;
// }

// double arithmetic_calculations(char *output, int is_graph, double xValue, int *error_flag) {
//   char *trash;
//   int top = -1;
//   int n_num = 0;
//   double x = 0.0;
//   double y = 0.0;
//   double num = 0.0;
//   double num_buffer[SIZE];
//   for (int i = 0; output[i]; i++) {
//     while (output[i] == '-' &&
//            (output[i + 1] == '-' || isdigit(output[i + 1]))) {
//       n_num++;
//       i++;
//     }
//     if (isdigit(output[i]) || output[i] == '.' || output[i] == 'x') {
//       num = strtod(&output[i], &trash);
//       if (output[i] == 'x') {
//         num = xValue;
//       }
//       if (trash[0] == '-') {
//         n_num++;
//         if (n_num % 2 != 0) {
//           num = -num;
//         }
//         n_num = 0;
//       }
//       i = trash - output;
//       set_num(num_buffer, &top, num);
//     } else {
//       switch (output[i]) {
//       case '+':
//         *error_flag = get_nums_func(num_buffer, &top, &x, &y);
//         set_num(num_buffer, &top, y + x);
//         break;
//       case '-':
//         *error_flag = get_nums_func(num_buffer, &top, &x, &y);
//         set_num(num_buffer, &top, y - x);
//         break;
//       case '*':
//         *error_flag = get_nums_func(num_buffer, &top, &x, &y);
//         set_num(num_buffer, &top, y * x);
//         break;
//       case '/':
//         *error_flag = get_nums_func(num_buffer, &top, &x, &y);
//         if (x == 0.0) {
//           *error_flag = 2;
//         }
//         set_num(num_buffer, &top, y / x);
//         break;
//       case '^':
//         *error_flag = get_nums_func(num_buffer, &top, &x, &y);
//         set_num(num_buffer, &top, pow(y, x));
//         break;
//       case 'm':
//         *error_flag = get_nums_func(num_buffer, &top, &x, &y);
//         set_num(num_buffer, &top, fmod(y, x));
//         break;
//       case 'c':
//         x = get_num(num_buffer, &top);
//         if (!is_graph) {
//           set_num(num_buffer, &top, cos(x * M_PI / 180));
//         } else {
//           set_num(num_buffer, &top, cos(x));
//         }
//         break;
//       case 's':
//         x = get_num(num_buffer, &top);
//         if (!is_graph) {
//           set_num(num_buffer, &top, sin(x * M_PI / 180));
//         } else {
//           set_num(num_buffer, &top, sin(x));
//         }
//         break;
//       case 't':
//         x = get_num(num_buffer, &top);
//         if (!is_graph) {
//           set_num(num_buffer, &top, tan(x * M_PI / 180));
//         } else {
//           set_num(num_buffer, &top, tan(x));
//         }
//         break;
//       case 'C':
//         x = get_num(num_buffer, &top);
//         if (!is_graph) {
//           set_num(num_buffer, &top, acos(x * M_PI / 180));
//         } else {
//           set_num(num_buffer, &top, acos(x));
//         }
//         break;
//       case 'S':
//         x = get_num(num_buffer, &top);
//         if (!is_graph) {
//           set_num(num_buffer, &top, asin(x * M_PI / 180));
//         } else {
//           set_num(num_buffer, &top, asin(x));
//         }
//         break;
//       case 'T':
//         x = get_num(num_buffer, &top);
//         if (!is_graph) {
//           set_num(num_buffer, &top, atan(x * M_PI / 180));
//         } else {
//           set_num(num_buffer, &top, atan(x));
//         }
//         break;
//       case '~':
//         x = get_num(num_buffer, &top);
//         set_num(num_buffer, &top, sqrt(x));
//         break;
//       case '|':
//         x = get_num(num_buffer, &top);
//         set_num(num_buffer, &top, fabs(x));
//         break;
//       case 'l':
//         x = get_num(num_buffer, &top);
//         set_num(num_buffer, &top, log(x));
//         break;
//       case 'L':
//         x = get_num(num_buffer, &top);
//         set_num(num_buffer, &top, log10(x));
//         break;
//       }
//     }
//   }
//   return get_num(num_buffer, &top);
// }

double s21::calculator::Notation() {
  for (size_t i = 0; i < str_.size(); i++) {
    InsertNumOutput(&i);
    switch (str_[i]) {
      case '^':
      case 'c':
      case 's':
      case 't':
      case 'a':
      case 'l':
      case '(':
        PushFunctions(&i);
        break;
      case 'm':
        do_pop(stack, output, &index, 1);
        stack_.push('m');
        break;
      case '*':
        do_pop(stack, output, &index, 5);
        stack_.push('*');
        break;
      case '/':
        do_pop(stack, output, &index, 5);
        stack_.push('/');
        break;
      case '+':
        do_pop(stack, output, &index, 1);
        stack_.push('+');
        break;
      case '-':
        if (str[i - 1] != '(') {
          do_pop(stack, output, &index, 1);
          stack_.push('-');
        }
        break;
      case ')':
        *error_flag = do_pop(stack, output, &index, 3);
        if (*error_flag == 0) {
          stack_.pop();
          do_pop(stack, output, &index, 4);
        }
        break;
      case 'x':
        is_graph_ = true;
        break;
      case '\0':
        do_pop(stack, output, &index, 2);
        break;
    }
  }
  result = arithmetic_calculations(output, is_graph, xValue, error_flag);
  return result;
}