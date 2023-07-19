#ifndef SRC_VALIDATOR_VALIDATOR_DEPOSIT_H_
#define SRC_VALIDATOR_VALIDATOR_DEPOSIT_H_

#include <QtGui>
#include <iostream>

namespace s21 {
class ValidatorDeposit {
 public:
  ValidatorDeposit() {}
  ~ValidatorDeposit() {}

  bool IsCorrectInt(const QString &str) const noexcept;
  bool IsCorrectDec(const QString &str) const noexcept;
};
}  // namespace s21

#endif  // SRC_VALIDATOR_VALIDATOR_DEPOSIT_H_
