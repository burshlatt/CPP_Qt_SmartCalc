#ifndef SRC_CONTROLLER_CONTROLLER_CREDIT_H_
#define SRC_CONTROLLER_CONTROLLER_CREDIT_H_

#include <QtGui>
#include <vector>
#include <iostream>

#include "../model/model_credit.h"

namespace s21 {
class ControllerCredit {
 public:
  ControllerCredit() {}
  ~ControllerCredit() {}

  void set_sum(const double &sum) noexcept;
  void set_term(const double &term) noexcept;
  void set_percent(const QString &percent) noexcept;

  QVector<QString> AnnuCred() noexcept;
  QVector<QString> DifferCred() noexcept;

 private:
  s21::ModelCredit model_;
};
}  // namespace s21

#endif  // SRC_CONTROLLER_CONTROLLER_CREDIT_H_
