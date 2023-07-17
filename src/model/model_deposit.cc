#include "model_deposit.h"

namespace s21 {
/*
  ================================= ACCESSORS =================================
*/
std::array<double, 4> ModelDeposit::get_depos() const noexcept { return depos_arr_; }
/*
  ================================= ACCESSORS =================================
*/

/*
  ================================= MUTATORS ==================================
*/
void ModelDeposit::set_sum(const double &sum) noexcept { sum_ = sum; }
void ModelDeposit::set_tax(const double &tax) noexcept { tax_ = tax; }
void ModelDeposit::set_cap(const bool &cap) noexcept { is_cap_ = cap; }
void ModelDeposit::set_term(const double &term) noexcept { term_ = term; }
void ModelDeposit::set_period(const double &period) noexcept { period_ = period; }
void ModelDeposit::set_percent(const double &percent) noexcept { percent_ = percent; }
void ModelDeposit::set_add(const std::vector<double> &add) noexcept { add_sum_ = add; }
void ModelDeposit::set_add_days(const std::vector<int> &days) noexcept { add_days_ = days; }
void ModelDeposit::set_waste(const std::vector<double> &waste) noexcept { waste_sum_ = waste; }
void ModelDeposit::set_waste_days(const std::vector<int> &days) noexcept { waste_days_ = days; }
void ModelDeposit::set_period_add(const std::vector<int> &period) noexcept { add_period_ = period; }
void ModelDeposit::set_period_waste(const std::vector<int> &period) noexcept { waste_period_ = period; }
/*
  ================================= MUTATORS ==================================
*/

/*
  ==================== D E P O S I T - C A L C U L A T O R ====================
*/

int ModelDeposit::FormatTime() const noexcept {
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

int ModelDeposit::FormatTimeAdd(const int &period) const noexcept {
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

void ModelDeposit::Deposit() noexcept {
  double total_ = sum_;
  int payments_time_ = FormatTime();
  double interest = 0.0;
  percent_ = (percent_ / 365) / 100;
  double added_sum_ = 0.0;
  double wasted_sum_ = 0.0;
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
    for (size_t j = 0; j < add_days_.size(); j++) {
      int add_time_ = FormatTimeAdd(add_period_[j]);
      if (i % add_time_ == 0 && add_time_ && i >= add_days_[j]) {
        total_ += add_sum_[j];
        added_sum_ += add_sum_[j];
      }
    }
    for (size_t k = 0; k < waste_days_.size(); k++) {
      int waste_time_ = FormatTimeAdd(waste_period_[k]);
      if (i % waste_time_ == 0 && waste_time_ && i >= waste_days_[k]) {
        total_ -= waste_sum_[k];
        wasted_sum_ += waste_sum_[k];
      }
    }
  }
  if (is_cap_) {
    depos_arr_[0] = total_ - sum_;  // RESULT PERCENT
    depos_arr_[0] -= added_sum_;
    depos_arr_[0] += wasted_sum_;
  } else {
    depos_arr_[0] = interest;  // RESULT PERCENT
  }
  depos_arr_[1] = (depos_arr_[0] - 7.5 / 100 * 1000000) > 0
                      ? (depos_arr_[0] - 7.5 / 100 * 1000000) * (tax_ / 100)
                      : 0;                        // TAX RATE
  depos_arr_[2] = depos_arr_[0] - depos_arr_[1];  // RESULT SUM WITH TAX
  depos_arr_[3] = total_;                         // RESULT SUM
}

/*
  ==================== D E P O S I T - C A L C U L A T O R ====================
*/
}  // namespace s21
