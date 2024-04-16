#include "model_credit.h"

namespace s21 {
/*
  ================================= ACCESSORS =================================
*/
std::vector<double> ModelCredit::get_cred() const noexcept { return cred_arr_; }
/*
  ================================= ACCESSORS =================================
*/

/*
  ================================= MUTATORS ==================================
*/
void ModelCredit::set_sum(const double &sum) noexcept { sum_ = sum; }
void ModelCredit::set_term(const double &term) noexcept { term_ = term; }
void ModelCredit::set_percent(const double &percent) noexcept { percent_ = percent; }
/*
  ================================= MUTATORS ==================================
*/

/*
  ===================== C R E D I T - C A L C U L A T O R =====================
*/

void ModelCredit::AnnuCred() noexcept {
  cred_arr_.clear();
  cred_arr_.push_back(std::round(sum_ * (((percent_ / (term_ * 100)) * pow(1 + (percent_ / (term_ * 100)), term_))
                      / (pow(1 + (percent_ / (term_ * 100)), term_) - 1)) * 100) / 100);  // MONTH PAY
  cred_arr_.push_back(cred_arr_.back() * term_ - sum_);  // OVERPAY
  cred_arr_.push_back(sum_ + cred_arr_.back());          // RESULT SUM
}

void ModelCredit::DifferCred() noexcept {
  cred_arr_.clear();
  double sum_copy_ = sum_;
  double term_copy_ = term_;
  cred_arr_.push_back(0);  // RESULT SUM
  while (term_copy_ != 0) {
    cred_arr_.push_back((sum_ / term_) + (sum_copy_ * percent_ / (term_ * 100)));  // PAYMENTS
    cred_arr_[0] += cred_arr_.back();
    sum_copy_ -= (sum_ / term_);
    term_copy_--;
  }
  cred_arr_.push_back(cred_arr_[0] - sum_);  // OVERPAY
}

/*
  ===================== C R E D I T - C A L C U L A T O R =====================
*/
}  // namespace s21
