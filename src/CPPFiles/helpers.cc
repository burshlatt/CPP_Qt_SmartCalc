#include "calculator.h"

void s21::calculator::print() {
  cout << endl;
  cout << "Размер стека: " << stack_.size() << endl;
  cout << "Стек: ";
  cout << stack_.top() << " ";
  // while (!stack_.empty()) {
  //   cout << stack_.top() << " ";
  //   stack_.pop();
  // }
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
    char char_str_[255] = {'\0'};
    for (auto i = 0; isdigit(str_[*index]); i++) {
      char_str_[i] = str_[(*index)++];
    }
    output_.push_back(std::string(char_str_));
  }
}

void s21::calculator::PushLogic(size_t *index, const std::string other) {
  if (other == "mod") {
    while (stack_.top() == "*" || stack_.top() == "/" || stack_.top() == "mod") {
      output_.push_back(stack_.top());
      stack_.pop();
    }
    index += 2;
  } else if (other == "*") {
    while (stack_.top() == "mod" || stack_.top() == "/" || stack_.top() == "*") {
      output_.push_back(stack_.top());
      stack_.pop();
    }
  } else if (other == "/") {
    while (stack_.top() == "mod" || stack_.top() == "*" || stack_.top() == "/") {
      output_.push_back(stack_.top());
      stack_.pop();
    }
  } else if (other == "+") {
    while (stack_.top() == "mod" || stack_.top() == "*" || stack_.top() == "/" || stack_.top() == "-" || stack_.top() == "+") {
      output_.push_back(stack_.top());
      stack_.pop();
    }
  } else if (other == "-") {
    while (stack_.top() == "mod" || stack_.top() == "*" || stack_.top() == "/" || stack_.top() == "+" || stack_.top() == "-") {
      output_.push_back(stack_.top());
      stack_.pop();
    }
  }
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
        PushLogic(index, "mod");
        stack_.push("mod");
        break;
      case '*':
        PushLogic(index, "*");
        stack_.push("*");
        break;
      case '/':
        PushLogic(index, "/");
        stack_.push("/");
        break;
      case '+':
        PushLogic(index, "+");
        stack_.push("+");
        break;
      case '-':
        if (str_[*index - 1] == '(') {
          output_.push_back("--");
        } else {
          PushLogic(index, "-");
          stack_.push("-");
        }
        break;
    }
  }
}

void s21::calculator::PopFunctions(const int variant) {
  if (variant == 1) {
    while (stack_.top() != "(" && !stack_.empty()) {
      output_.push_back(stack_.top());
      stack_.pop();
    }
    if (stack_.empty()) {
      is_error_ = true;
    } else {
      stack_.pop();
      for (size_t i = 0; i < functions_.size(); i++) {
        if (stack_.top() == functions_[i]) {
          output_.push_back(stack_.top());
          stack_.pop();
        }
      }
    }
  } else if (variant == 2) {
    if (stack_.top() == "(" || stack_.top() == ")") {
      is_error_ = true;
    } else {
      while (!stack_.empty()) {
        output_.push_back(stack_.top());
        stack_.pop();
      }
    }
  }
}

void s21::calculator::test() {
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
}

int main () {
  s21::calculator test_1;
  std::string string_math_ = "cos(56)*sin(87)/tan(66)+acos(22)-asin(55)*(atan(99)/log(77)+ln(66))^(2+3)+4mod2";
  test_1.set_str(string_math_);
  test_1.test();
  test_1.print();
  return 0;
}
