#include "calculator.h"

void s21::calculator::print() {
  cout << endl;
  cout << "Размер стека: " << output_.size() << endl;
  cout << "Стек: ";
  while (output_.size()) {
    cout << output_.top() << " ";
    output_.pop();
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
  char char_str_[255] = {'\0'};
  for (auto i = 0; isdigit(str_[*index]); i++) {
    char_str_[i] = str_[(*index)++];
  }
  if (*char_str_) {
    output_.push(std::string(char_str_));
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
        stack_.push("mod");
        *index += 2;
        break;
      case '*':
        stack_.push("*");
        break;
      case '/':
        stack_.push("/");
        break;
      case '+':
        stack_.push("+");
        break;
      case '-':
        if (str_[*index - 1] == '(') {
          output_.push("--");
        } else {
          stack_.push("-");
        }
        break;
    }
  }
}

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
        // PopFunctions(&index, 5);
        PushFunctions(&i, 2);
        break;
      case ')':
        // PopFunctions(&index, 3);
        // if (*error_flag == 0) {
        //   stack_.pop();
        //   PopFunctions(&index, 4);
        // }
        break;
      case 'x':
        is_graph_ = true;
        break;
      case '\0':
        // PopFunctions(&index, 2);
        break;
    }
  }
}

int main () {
  s21::calculator test_1;
  std::string string_math_ = "cos(56)-sin(87)+tan(66)*atan(-(-99+33))+3^2-(5-33)";
  test_1.set_str(string_math_);
  test_1.test();
  test_1.print();
  return 0;
}
