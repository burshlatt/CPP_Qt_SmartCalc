#ifndef SRC_MODEL_MODEL_H_
#define SRC_MODEL_MODEL_H_

#include <array>
#include <cmath>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

namespace s21 {
class Model {
 public:
  Model() {}
  ~Model() {}

  bool get_error() const noexcept;
  double get_res() const noexcept;
  std::vector<double> get_cred() const noexcept;
  std::array<double, 4> get_depos() const noexcept;

  void set_x(const double &num) noexcept;
  void set_cap(const bool &cap) noexcept;
  void set_rad(const bool &graph) noexcept;
  void set_sum(const double &sum) noexcept;
  void set_tax(const double &tax) noexcept;
  void set_term(const double &term) noexcept;
  void set_period(const double &period) noexcept;
  void set_percent(const double &percent) noexcept;
  void set_add(const std::vector<double> &add) noexcept;
  void set_add_days(const std::vector<int> &days) noexcept;
  void set_waste(const std::vector<double> &waste) noexcept;
  void set_waste_days(const std::vector<int> &days) noexcept;
  void set_period_add(const std::vector<int> &period) noexcept;
  void set_period_waste(const std::vector<int> &period) noexcept;

  void Deposit() noexcept;
  void GetNums() noexcept;
  void AnnuCred() noexcept;
  void DifferCred() noexcept;
  void ClearOutput() noexcept;
  void Calculations() noexcept;
  void PopFunctions() noexcept;
  void DoCalculations() noexcept;
  int FormatTime() const noexcept;
  void GetNums(double &x) noexcept;
  bool ConvertNums(const size_t &i) noexcept;
  void PushFunctions(size_t &index) noexcept;
  void GetNums(double &x, double &y) noexcept;
  void InsertNumOutput(size_t &index) noexcept;
  void Notation(const std::string &str) noexcept;
  void PushLogic(const std::string &str) noexcept;
  int FormatTimeAdd(const int &period) const noexcept;
  int FormatTimeWaste(const int &period) const noexcept;

 private:
  int pos_ = 0;
  int option_ = 0;
  std::string str_;
  std::string func_;
  bool is_cap_ = false;
  bool is_rad_ = false;
  bool is_error_ = false;
  double sum_ = 0.0;
  double tax_ = 0.0;
  double term_ = 0.0;
  double result_ = 0.0;
  double period_ = 0.0;
  double percent_ = 0.0;
  double x_value_ = 0.0;
  double x_ = 0.0, y_ = 0.0;
  std::vector<int> add_count_;
  std::vector<int> waste_count_;
  std::vector<int> add_period_;
  std::vector<int> waste_period_;
  std::vector<double> add_sum_;
  std::vector<double> waste_sum_;
  std::vector<double> cred_arr_;
  std::array<double, 4> depos_arr_;
  std::stack<double> num_buffer_;
  std::stack<std::string> stack_;
  std::array<std::string, 256> output_;
  const std::array<std::string, 11> functions_ = {"cos",  "sin",  "tan", "acos",
                                                  "asin", "atan", "ln",  "log",
                                                  "sqrt", "abs",  "^"};
};
}  // namespace s21

#endif  // SRC_MODEL_MODEL_H_
