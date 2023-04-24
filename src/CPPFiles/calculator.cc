#include "calculator.h"

void s21::calculator::print() {
  cout << endl;
  cout << "Размер стека: " << stack_.size() << endl;
  cout << "Стек: ";
  while (!stack_.empty()) {
    cout << stack_.top() << " ";
    stack_.pop();
  }
  cout << "\nРазмер выходной строки: " << output_.size() << endl;
  cout << "Выходная строка: ";
  for (size_t i = 0; i < output_.size(); i++) {
    cout << output_[i] << " ";
  }
  cout << endl << endl;
}

std::string s21::calculator::get_str() const noexcept {
  return str_;
}

void s21::calculator::set_str(const std::string other) noexcept {
  str_ = other;
}

void s21::calculator::InsertNumOutput(size_t *index) {
  if (isdigit(str_[*index])) {
    bool is_negative_ = false;
    if (str_[*index - 1] == '-' && str_[*index - 2] == '(') {
      is_negative_ = true;
    }
    char char_str_[255] = {'\0'};
    for (auto i = 0; isdigit(str_[*index]) || str_[*index] == '.'; i++) {
      char_str_[i] = str_[(*index)++];
    }
    if (is_negative_) {
      output_.push_back(std::string(char_str_) + "-");
    } else {
      output_.push_back(std::string(char_str_));
    }
  }
}

void s21::calculator::PushLogic(const std::string other) {
  if (other == "mod" || other == "*" || other == "/") {
    while (!stack_.empty() && (stack_.top() == "mod" || stack_.top() == "*" || stack_.top() == "/")) {
      output_.push_back(stack_.top());
      stack_.pop();
    }
  } else if (other == "+" || other == "-") {
    while (!stack_.empty() && (stack_.top() == "mod" || stack_.top() == "*" || stack_.top() == "/" || stack_.top() == "+" || stack_.top() == "-")) {
      output_.push_back(stack_.top());
      stack_.pop();
    }
  }
  stack_.push(other);
}

void s21::calculator::PushFunctions(size_t *index, const int variant) {
  if (variant == 1) {
    if (str_[*index] == '^') {
      stack_.push("^");
    } else {
      char buffer[255] = {'\0'};
      for (size_t i = 0; str_[*index] != '('; i++) {
        buffer[i] = str_[(*index)++];
      }
      if (std::string(buffer).size()) {
        stack_.push(std::string(buffer));
      }
      stack_.push("(");
    }
  } else if (variant == 2) {
    switch (str_[*index]) {
      case 'm':
        PushLogic("mod");
        *index += 2;
        break;
      case '*':
        PushLogic("*");
        break;
      case '/':
        PushLogic("/");
        break;
      case '+':
        PushLogic("+");
        break;
      case '-':
        if (str_[*index - 1] != '(' || !isdigit(str_[*index + 1])) {
          PushLogic("-");
        }
        break;
    }
  }
}

void s21::calculator::PopFunctions(const int variant) {
  if (variant == 1) {
    while (!stack_.empty() && stack_.top() != "(") {
      output_.push_back(stack_.top());
      stack_.pop();
    }
    if (stack_.empty()) {
      is_error_ = true;
    } else {
      stack_.pop();
      for (size_t i = 0; i < functions_.size() && !stack_.empty(); i++) {
        if (stack_.top() == functions_[i]) {
          output_.push_back(stack_.top());
          stack_.pop();
        }
      }
    }
  } else if (variant == 2) {
    while (!stack_.empty() && !is_error_) {
      if (stack_.top() == "(") {
        is_error_ = true;
      } else {
        output_.push_back(stack_.top());
        stack_.pop();
      }
    }
  }
}

bool s21::calculator::CustomIsDigit(const std::string other) {
  return (other.front() >= '0' && other.front() <= '9') ? true : false;
}

bool s21::calculator::IsNegative(const std::string other) {
  return other.back() == '-'  ? true : false;
}

void s21::calculator::Notation() {
  for (size_t i = 0; i < str_.size() && !is_error_; i++) {
    InsertNumOutput(&i);
    switch (str_[i]) {
      case 'c':
      case 's':
      case 't':
      case 'a':
      case 'l':
      case '^':
      case '(':
        PushFunctions(&i, 1);
        break;
      case 'm':
      case '*':
      case '/':
      case '+':
      case '-':
        PushFunctions(&i, 2);
        break;
      case ')':
        PopFunctions(1);
        break;
      case 'x':
        is_graph_ = true;
        break;
      case '\0':
        PopFunctions(2);
        break;
    }
  }
  output_.shrink_to_fit();
  Calculations();
}

void s21::calculator::Calculations() {
  // double x = 0.0;
  // double y = 0.0;
  double num = 0.0;
  for (size_t i = 0; i < output_.size(); i++) {
    if (CustomIsDigit(output_[i]) || output_[i] == "x") {
      if (output_[i] == "x") {
        num = x_value_;
      } else {
        num = atof(output_[i].c_str());
      }
      if (IsNegative(output_[i])) {
        num = -num;
      }
      num_buffer_.push(num);
      // cout << num_buffer_.top() << " ";
    } else {}
    //   switch (output[i]) {
    //   case '+':
    //     *error_flag = get_nums_func(num_buffer, &top, &x, &y);
    //     set_num(num_buffer, &top, y + x);
    //     break;
    //   case '-':
    //     *error_flag = get_nums_func(num_buffer, &top, &x, &y);
    //     set_num(num_buffer, &top, y - x);
    //     break;
    //   case '*':
    //     *error_flag = get_nums_func(num_buffer, &top, &x, &y);
    //     set_num(num_buffer, &top, y * x);
    //     break;
    //   case '/':
    //     *error_flag = get_nums_func(num_buffer, &top, &x, &y);
    //     if (x == 0.0) {
    //       *error_flag = 2;
    //     }
    //     set_num(num_buffer, &top, y / x);
    //     break;
    //   case '^':
    //     *error_flag = get_nums_func(num_buffer, &top, &x, &y);
    //     set_num(num_buffer, &top, pow(y, x));
    //     break;
    //   case 'm':
    //     *error_flag = get_nums_func(num_buffer, &top, &x, &y);
    //     set_num(num_buffer, &top, fmod(y, x));
    //     break;
    //   case 'c':
    //     x = get_num(num_buffer, &top);
    //     if (!is_graph) {
    //       set_num(num_buffer, &top, cos(x * M_PI / 180));
    //     } else {
    //       set_num(num_buffer, &top, cos(x));
    //     }
    //     break;
    //   case 's':
    //     x = get_num(num_buffer, &top);
    //     if (!is_graph) {
    //       set_num(num_buffer, &top, sin(x * M_PI / 180));
    //     } else {
    //       set_num(num_buffer, &top, sin(x));
    //     }
    //     break;
    //   case 't':
    //     x = get_num(num_buffer, &top);
    //     if (!is_graph) {
    //       set_num(num_buffer, &top, tan(x * M_PI / 180));
    //     } else {
    //       set_num(num_buffer, &top, tan(x));
    //     }
    //     break;
    //   case 'C':
    //     x = get_num(num_buffer, &top);
    //     if (!is_graph) {
    //       set_num(num_buffer, &top, acos(x * M_PI / 180));
    //     } else {
    //       set_num(num_buffer, &top, acos(x));
    //     }
    //     break;
    //   case 'S':
    //     x = get_num(num_buffer, &top);
    //     if (!is_graph) {
    //       set_num(num_buffer, &top, asin(x * M_PI / 180));
    //     } else {
    //       set_num(num_buffer, &top, asin(x));
    //     }
    //     break;
    //   case 'T':
    //     x = get_num(num_buffer, &top);
    //     if (!is_graph) {
    //       set_num(num_buffer, &top, atan(x * M_PI / 180));
    //     } else {
    //       set_num(num_buffer, &top, atan(x));
    //     }
    //     break;
    //   case '~':
    //     x = get_num(num_buffer, &top);
    //     set_num(num_buffer, &top, sqrt(x));
    //     break;
    //   case '|':
    //     x = get_num(num_buffer, &top);
    //     set_num(num_buffer, &top, fabs(x));
    //     break;
    //   case 'l':
    //     x = get_num(num_buffer, &top);
    //     set_num(num_buffer, &top, log(x));
    //     break;
    //   case 'L':
    //     x = get_num(num_buffer, &top);
    //     set_num(num_buffer, &top, log10(x));
    //     break;
    //   }
    // }
  }
  // return get_num(num_buffer, &top);
}

int main () {
  s21::calculator test_;
  test_.set_str("cos(56.33)*sin(87)+(-(-3+5))/tan(66)+acos(22)-asin(55)*(atan(99)/log(77)+ln(66))^(2+3)+4mod2");
  test_.Notation();
  test_.print();
  return 0;
}
