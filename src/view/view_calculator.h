#ifndef VIEW_CALCULATOR_H
#define VIEW_CALCULATOR_H

#include <QMainWindow>

#include "view_credit.h"
#include "view_deposit.h"
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
  void CheckFields() noexcept;
  void FuncClicked() noexcept;
  void on_rad_clicked() noexcept;
  void on_deg_clicked() noexcept;
  void SymbolsClicked() noexcept;
  void BracketsClicked() noexcept;
  void OperatorsClicked() noexcept;
  void on_dotSym_clicked() noexcept;
  void on_delAll_clicked() noexcept;
  void on_subFunc_clicked() noexcept;
  void on_delElem_clicked() noexcept;
  void on_credCalc_clicked() noexcept;
  void on_deposCalc_clicked() noexcept;
  void on_showGraph_clicked() noexcept;
  void on_resultFunc_clicked() noexcept;

 private:
  Ui::ViewCalculator *ui_;
  ViewCredit *credit_;
  ViewDeposit *deposit_;

  std::string str_;
  QPushButton *button_;
  s21::ControllerCalculator calc_;

  size_t size_ = 0;
  bool is_dot_ = false;
  bool graph_open_ = false;
  const std::array<char, 7> operators_skip_ = {'-', '+', '*', '/', '^', 'd', '('};
};

#endif  // VIEW_CALCULATOR_H
