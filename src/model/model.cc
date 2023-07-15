#include "model.h"

namespace s21 {
/*
  ============================ CALCULATOR ACCESSORS ===========================
*/
double Model::get_res() const noexcept { return result_; }
bool Model::get_error() const noexcept { return is_error_; }
/*
  ============================ CALCULATOR ACCESSORS ===========================
*/

/*
  ======================== CREDIT && DEPOSIT ACCESSORS ========================
*/
std::vector<double> Model::get_cred() const noexcept { return cred_arr_; }
std::array<double, 4> Model::get_depos() const noexcept { return depos_arr_; }
/*
  ======================== CREDIT && DEPOSIT ACCESSORS ========================
*/

/*
  ============================ CALCULATOR MUTATORS ============================
*/
void Model::set_x(const double &num) noexcept { x_value_ = num; }
void Model::set_rad(const bool &graph) noexcept { is_rad_ = graph; }
/*
  ============================ CALCULATOR MUTATORS ============================
*/

/*
  ========================= CREDIT && DEPOSIT MUTATORS ========================
*/
void Model::set_sum(const double &sum) noexcept { sum_ = sum; }
void Model::set_tax(const double &tax) noexcept { tax_ = tax; }
void Model::set_cap(const bool &cap) noexcept { is_cap_ = cap; }
void Model::set_term(const double &term) noexcept { term_ = term; }
void Model::set_period(const double &period) noexcept { period_ = period; }
void Model::set_percent(const double &percent) noexcept { percent_ = percent; }
void Model::set_add(const std::vector<double> &add) noexcept { add_sum_ = add; }
void Model::set_waste(const std::vector<double> &waste) noexcept {
  waste_sum_ = waste;
}
void Model::set_add_days(const std::vector<int> &days) noexcept {
  add_count_ = days;
}
void Model::set_waste_days(const std::vector<int> &days) noexcept {
  waste_count_ = days;
}
void Model::set_period_add(const std::vector<int> &period) noexcept {
  add_period_ = period;
}
void Model::set_period_waste(const std::vector<int> &period) noexcept {
  waste_period_ = period;
}
/*
  ========================= CREDIT && DEPOSIT MUTATORS ========================
*/

/*
  ============================ C A L C U L A T O R ============================
*/
void Model::GetNums(double &x) noexcept {
  x = num_buffer_.top();
  num_buffer_.pop();
}

void Model::GetNums(double &x, double &y) noexcept {
  x = num_buffer_.top();
  num_buffer_.pop();
  y = num_buffer_.top();
  num_buffer_.pop();
}

void Model::GetNums() noexcept {
  if (option_ == 1) {
    GetNums(x_);
  } else if (option_ == 2) {
    GetNums(x_, y_);
  } else if (option_ == 3) {
    GetNums(x_);
    x_ = is_rad_ ? x_ : x_ * M_PI / 180;
  } else if (option_ == 4) {
    const double n_num_ = num_buffer_.top();
    num_buffer_.pop();
    num_buffer_.push(-n_num_);
  }
}

void Model::InsertNumOutput(size_t &index) noexcept {
  if (isdigit(str_[index]) || str_[index] == 'x' || str_[index] == 'P') {
    int i = 0;
    bool is_negative_ = false;
    char char_str_[255] = {'\0'};
    if (str_[index - 1] == '-' && str_[index - 2] == '(') is_negative_ = true;
    while (isdigit(str_[index]) || str_[index] == '.' || str_[index] == 'x' ||
           str_[index] == 'P' || str_[index] == 'i') {
      char_str_[i++] = str_[index++];
    }
    output_[pos_++] =
        is_negative_ ? std::string(char_str_) + "-" : std::string(char_str_);
  }
}

void Model::PushLogic(const std::string &str) noexcept {
  if (str == "mod" || str == "*" || str == "/") {
    while (!stack_.empty() && (stack_.top() == "mod" || stack_.top() == "*" ||
                               stack_.top() == "/" || stack_.top() == "^" ||
                               stack_.top() == "!")) {
      output_[pos_++] = stack_.top();
      stack_.pop();
    }
  } else if (str == "+" || str == "-") {
    while (!stack_.empty() &&
           (stack_.top() == "mod" || stack_.top() == "*" ||
            stack_.top() == "/" || stack_.top() == "+" || stack_.top() == "-" ||
            stack_.top() == "^" || stack_.top() == "!")) {
      output_[pos_++] = stack_.top();
      stack_.pop();
    }
  }
  stack_.push(str);
}

void Model::PushFunctions(size_t &index) noexcept {
  if (option_ == 1) {
    if (str_[index] == '^') {
      stack_.push("^");
    } else {
      char buffer_[255] = {'\0'};
      for (size_t i = 0; str_[index] != '('; i++) buffer_[i] = str_[index++];
      if (std::string(buffer_).size()) stack_.push(std::string(buffer_));
      stack_.push("(");
    }
  } else if (option_ == 2) {
    if (str_[index] == 'm') {
      PushLogic("mod");
      index += 2;
    } else if (str_[index] == '*') {
      PushLogic("*");
    } else if (str_[index] == '/') {
      PushLogic("/");
    } else if (str_[index] == '+') {
      PushLogic("+");
    } else if (str_[index] == '-') {
      if (str_[index - 1] == '(' && !isdigit(str_[index + 1]) &&
          str_[index + 1] != 'P' && str_[index + 1] != 'x')
        PushLogic("!");
      else if (str_[index - 1] != '(')
        PushLogic("-");
    }
  }
}

void Model::PopFunctions() noexcept {
  if (option_ == 1) {
    while (!stack_.empty() && stack_.top() != "(") {
      output_[pos_++] = stack_.top();
      stack_.pop();
    }
    if (stack_.empty()) {
      is_error_ = true;
    } else {
      stack_.pop();
      for (size_t i = 0; i < functions_.size() && !stack_.empty(); i++) {
        if (stack_.top() == functions_[i]) {
          output_[pos_++] = stack_.top();
          stack_.pop();
        }
      }
    }
  } else if (option_ == 2) {
    while (!stack_.empty() && !is_error_) {
      if (stack_.top() == "(") {
        is_error_ = true;
      } else {
        output_[pos_++] = stack_.top();
        stack_.pop();
      }
    }
  }
}

bool Model::ConvertNums(const size_t &i) noexcept {
  double num_ = 0.0;
  if (isdigit(output_[i].front()) || output_[i].front() == 'x' ||
      output_[i].front() == 'P') {
    if (output_[i].front() == 'x')
      num_ = x_value_;
    else if (output_[i].front() == 'P')
      num_ = M_PI;
    else
      num_ = atof(output_[i].c_str());
    if (output_[i].back() == '-') num_ = -num_;
    num_buffer_.push(num_);
    return true;
  }
  return false;
}

void Model::Notation(const std::string &str) noexcept {
  str_ = str;
  for (size_t i = 0; i < str_.size() && !is_error_; i++) {
    InsertNumOutput(i);
    switch (str_[i]) {
      case 'c':
      case 's':
      case 't':
      case 'a':
      case 'l':
      case '^':
      case '(':
        option_ = 1;
        PushFunctions(i);
        break;
      case 'm':
      case '*':
      case '/':
      case '+':
      case '-':
        option_ = 2;
        PushFunctions(i);
        break;
      case ')':
        option_ = 1;
        PopFunctions();
        break;
      case '=':
        option_ = 2;
        PopFunctions();
        break;
    }
  }
}

void Model::DoCalculations() noexcept {
  if (func_ == "+")
    num_buffer_.push(y_ + x_);
  else if (func_ == "-")
    num_buffer_.push(y_ - x_);
  else if (func_ == "*")
    num_buffer_.push(y_ * x_);
  else if (func_ == "/")
    num_buffer_.push(y_ / x_);
  else if (func_ == "ln")
    num_buffer_.push(log(x_));
  else if (func_ == "cos")
    num_buffer_.push(cos(x_));
  else if (func_ == "sin")
    num_buffer_.push(sin(x_));
  else if (func_ == "tan")
    num_buffer_.push(tan(x_));
  else if (func_ == "abs")
    num_buffer_.push(fabs(x_));
  else if (func_ == "acos")
    num_buffer_.push(acos(x_));
  else if (func_ == "asin")
    num_buffer_.push(asin(x_));
  else if (func_ == "atan")
    num_buffer_.push(atan(x_));
  else if (func_ == "sqrt")
    num_buffer_.push(sqrt(x_));
  else if (func_ == "log")
    num_buffer_.push(log10(x_));
  else if (func_ == "^")
    num_buffer_.push(pow(y_, x_));
  else if (func_ == "mod")
    num_buffer_.push(fmod(y_, x_));
}

void Model::Calculations() noexcept {
  for (int i = 0; i < pos_; i++) {
    if (!ConvertNums(i)) {
      switch (output_[i].front()) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case 'm':
          option_ = 2;
          break;
        case 'c':
        case 's':
        case 't':
        case 'a':
          option_ = output_[i] == "sqrt" || output_[i] == "abs" ? 1 : 3;
          break;
        case 'l':
          option_ = 1;
          break;
        case '!':
          option_ = 4;
          break;
      }
      func_ = output_[i];
      GetNums();
      DoCalculations();
    }
  }
  result_ = num_buffer_.top();
  num_buffer_.pop();
}

void Model::ClearOutput() noexcept { pos_ = 0; }

/*
  ============================ C A L C U L A T O R ============================
*/

/*
  ===================== C R E D I T - C A L C U L A T O R =====================
*/

void Model::AnnuCred() noexcept {
  cred_arr_.clear();
  cred_arr_.push_back(
      std::round(sum_ *
                 (((percent_ / (term_ * 100)) *
                   pow(1 + (percent_ / (term_ * 100)), term_)) /
                  (pow(1 + (percent_ / (term_ * 100)), term_) - 1)) *
                 100) /
      100);                                              // MONTH PAY
  cred_arr_.push_back(cred_arr_.back() * term_ - sum_);  // OVERPAY
  cred_arr_.push_back(sum_ + cred_arr_.back());          // RESULT SUM
}

void Model::DifferCred() noexcept {
  cred_arr_.clear();
  double sum_copy_ = sum_;
  double term_copy_ = term_;
  cred_arr_.push_back(0);  // RESULT SUM
  while (term_copy_ != 0) {
    cred_arr_.push_back((sum_ / term_) +
                        (sum_copy_ * percent_ / (term_ * 100)));  // PAYMENTS
    cred_arr_[0] += cred_arr_.back();
    sum_copy_ -= (sum_ / term_);
    term_copy_--;
  }
  cred_arr_.push_back(cred_arr_[0] - sum_);  // OVERPAY
}

/*
  ===================== C R E D I T - C A L C U L A T O R =====================
*/

/*
  ==================== D E P O S I T - C A L C U L A T O R ====================
*/

int Model::FormatTime() const noexcept {
  if (period_ == 1)
    return 1;
  else if (period_ == 2)
    return 7;
  else if (period_ == 3)
    return 30;
  else if (period_ == 4)
    return 91;
  else if (period_ == 5)
    return 183;
  else if (period_ == 6)
    return 365;
  else if (period_ == 7)
    return term_;
  return 0;
}

int Model::FormatTimeAdd(const int &period) const noexcept {
  if (period == 1)
    return term_;
  else if (period == 2)
    return 30;
  else if (period == 3)
    return 60;
  else if (period == 4)
    return 91;
  else if (period == 5)
    return 183;
  else if (period == 6)
    return 365;
  return 0;
}

int Model::FormatTimeWaste(const int &period) const noexcept {
  if (period == 1)
    return term_;
  else if (period == 2)
    return 30;
  else if (period == 3)
    return 60;
  else if (period == 4)
    return 91;
  else if (period == 5)
    return 183;
  else if (period == 6)
    return 365;
  return 0;
}

void Model::Deposit() noexcept {
  double total_ = sum_;
  int payments_time_ = FormatTime();
  double interest = 0.0;
  percent_ = (percent_ / 365) / 100;
  for (int i = 1; i <= term_; i++) {
    if (is_cap_) {
      interest += total_ * percent_;
      if (i % payments_time_ == 0 && payments_time_) {
        total_ += interest;
        interest = 0.0;
      }
    } else {
      interest += total_ * percent_;
    }
    for (size_t j = 0; j < add_count_.size(); j++) {
      int add_time_ = FormatTimeAdd(add_period_[j]);
      if (i % add_time_ == 0 && add_time_ && i >= add_count_[j])
        total_ += add_sum_[j];
    }
    for (size_t k = 0; k < waste_count_.size(); k++) {
      int waste_time_ = FormatTimeWaste(waste_period_[k]);
      if (i % waste_time_ == 0 && waste_time_ && i >= waste_count_[k])
        total_ -= waste_sum_[k];
    }
  }
  if (is_cap_) {
    depos_arr_[0] = total_ - sum_;  // RESULT PERCENT
  } else {
    depos_arr_[0] = interest;  // RESULT PERCENT
  }
  depos_arr_[1] = (depos_arr_[0] - 7.5 / 100 * 1000000) > 0
                      ? (depos_arr_[0] - 7.5 / 100 * 1000000) * 0.13
                      : 0;                        // TAX RATE
  depos_arr_[2] = depos_arr_[0] - depos_arr_[1];  // RESULT SUM WITH TAX
  depos_arr_[3] = total_;                         // RESULT SUM
}

/*
  ==================== D E P O S I T - C A L C U L A T O R ====================
*/
}  // namespace s21
