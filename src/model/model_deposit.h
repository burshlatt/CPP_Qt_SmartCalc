#ifndef SRC_MODEL_MODEL_DEPOSIT_H_
#define SRC_MODEL_MODEL_DEPOSIT_H_

#include <array>
#include <iostream>
#include <vector>

namespace s21 {
class ModelDeposit {
 public:
  ModelDeposit() {}
  ~ModelDeposit() {}

  std::array<double, 4> get_depos() const noexcept;

  void set_cap(const bool &cap) noexcept;
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
  int FormatTime() const noexcept;
  int FormatTimeAdd(const int &period) const noexcept;

 private:
  bool is_cap_ = false;
  double sum_ = 0.0;
  double tax_ = 0.0;
  double term_ = 0.0;
  double period_ = 0.0;
  double percent_ = 0.0;
  std::vector<int> add_days_;
  std::vector<int> waste_days_;
  std::vector<int> add_period_;
  std::vector<int> waste_period_;
  std::vector<double> add_sum_;
  std::vector<double> waste_sum_;
  std::array<double, 4> depos_arr_;
};
}  // namespace s21

#endif  // SRC_MODEL_MODEL_DEPOSIT_H_
