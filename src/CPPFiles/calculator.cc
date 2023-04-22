#include "calculator.h"

void s21::calculator::Notation() {
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
        PushFunctions(&i, 1);
        break;
      case 'm':
      case '*':
      case '/':
      case '+':
      case '-':
        PopFunctions(&index, 5);
        PushFunctions(&i, 2);
        break;
      case ')':
        PopFunctions(&index, 3);
        if (*error_flag == 0) {
          stack_.pop();
          PopFunctions(&index, 4);
        }
        break;
      case 'x':
        is_graph_ = true;
        break;
      case '\0':
        PopFunctions(&index, 2);
        break;
    }
  }
  // Calculations(output, is_graph, xValue, error_flag);
}
