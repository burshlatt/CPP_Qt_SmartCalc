#ifndef SRC_VALIDATOR_VALIDATOR_CREDIT_H_
#define SRC_VALIDATOR_VALIDATOR_CREDIT_H_

#include <QtGui>
#include <iostream>

namespace s21 {
class ValidatorCredit {
 public:
  ValidatorCredit() {}
  ~ValidatorCredit() {}

  bool IsCorrectInt(const QString &str) const noexcept;
  bool IsCorrectDec(const QString &str) const noexcept;
};
}  // namespace s21

#endif  // SRC_VALIDATOR_VALIDATOR_CREDIT_H_
