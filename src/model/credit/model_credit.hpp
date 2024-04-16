#ifndef SRC_MODEL_MODEL_CREDIT_H_
#define SRC_MODEL_MODEL_CREDIT_H_

#include <vector>

namespace s21 {
class ModelCredit {
 public:
  ModelCredit() {}
  ~ModelCredit() {}

  std::vector<double> get_cred() const noexcept;

  void set_sum(const double &sum) noexcept;
  void set_term(const double &term) noexcept;
  void set_percent(const double &percent) noexcept;

  void AnnuCred() noexcept;
  void DifferCred() noexcept;

 private:
  double sum_ = 0.0;
  double term_ = 0.0;
  double percent_ = 0.0;
  std::vector<double> cred_arr_;
};
}  // namespace s21

#endif  // SRC_MODEL_MODEL_CREDIT_H_
