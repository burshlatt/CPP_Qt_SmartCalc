#include "validator_deposit.h"

namespace s21 {
/*
  ============================ V A L I D A T O R S ============================
*/
bool ValidatorDeposit::IsCorrectInt(const QString &str) const noexcept {
  for (int i = 0; i < str.size(); i++) {
    if (str[i] < '0' || str[i] > '9') {
      return false;
    }
  }
  return true;
}

bool ValidatorDeposit::IsCorrectDec(const QString &str) const noexcept {
  for (int i = 0; i < str.size(); i++) {
    if (((str[i] < '0' || str[i] > '9') && str[i] != '.') || str.front() == '.' || str.back() == '.') {
      return false;
    }
  }
  return true;
}
/*
  ============================ V A L I D A T O R S ============================
*/
}  // namespace s21
