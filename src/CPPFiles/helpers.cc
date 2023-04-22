#include "calculator.h"

void s21::calculator::print() {
  cout << "Размер стека:\n" << stack_.size() << endl;
  cout << "Выходная строка:\n" << get_output() << endl;
}

std::string s21::calculator::get_str() const noexcept {
  return str_;
}

std::string s21::calculator::get_output() const noexcept {
  return output_;
}

void s21::calculator::set_str(const std::string other) noexcept {
  str_ = other;
}

void s21::calculator::set_output(const std::string other) noexcept {
  output_ += other;
}

void s21::calculator::InsertNumOutput(size_t *index) {
  char char_str_[255] = {'\0'};
  for (auto i = 0; isdigit(str_[*index]); i++) {
    char_str_[i] = str_[(*index)++];
  }
  output_ += std::string(char_str_);
  if (isdigit(output_[output_.size() - 1])) {
    output_ += " ";
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
  } else {
    switch (str_[*index]) {
      case '+':
        stack_.push("+");
        break;
      case '-':
        stack_.push("-");
        break;
      case '*':
        stack_.push("*");
        break;
      case '/':
        stack_.push("/");
        break;
      case 'm':
        stack_.push("mod");
        *index += 2;
        break;
    }
  }
}

void s21::calculator::test() {
  for (size_t i = 0; i < str_.size(); i++) {
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
}

int main () {
  s21::calculator test_1;
  std::string string_math_ = "cos(56)-sin(87)+tan(66)*atan(-(-99+33))+3^2-(5-3)";
  test_1.set_str(string_math_);
  test_1.test();
  // test_1.print();
  return 0;
}
