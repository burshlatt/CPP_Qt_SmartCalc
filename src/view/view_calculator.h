#ifndef VIEW_CALCULATOR_H
#define VIEW_CALCULATOR_H

#include <QMainWindow>

#include "view_credit.h"
#include "view_deposit.h"
#include "../validator/validator_calculator.h"
#include "../controller/controller_calculator.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class ViewCalculator;
}
QT_END_NAMESPACE

class ViewCalculator : public QMainWindow {
  Q_OBJECT

 public:
  ViewCalculator(QWidget *parent = nullptr);
  ~ViewCalculator();

 private slots:
  void GetInfo() noexcept;
  void PrintGraph() noexcept;
  void RadClicked() noexcept;
  void DegClicked() noexcept;
  void DotClicked() noexcept;
  void SubClicked() noexcept;
  void FuncClicked() noexcept;
  void ResultClicked() noexcept;
  void DelAllClicked() noexcept;
  bool IsCorrectGraph() noexcept;
  void DelElemClicked() noexcept;
  void SymbolsClicked() noexcept;
  void CredCalcClicked() noexcept;
  void BracketsClicked() noexcept;
  void OperatorsClicked() noexcept;
  void DeposCalcClicked() noexcept;
  void ShowGraphClicked() noexcept;

 private:
  Ui::ViewCalculator *ui_;
  ViewCredit *credit_;
  ViewDeposit *deposit_;

  std::string str_;
  QPushButton *button_;
  s21::ValidatorCalculator valid_;
  s21::ControllerCalculator calc_;

  size_t size_ = 0;
  bool is_dot_ = false;
  bool graph_open_ = false;
  const std::array<char, 7> operators_skip_ = {'-', '+', '*', '/', '^', 'd', '('};
};

#endif  // VIEW_CALCULATOR_H
