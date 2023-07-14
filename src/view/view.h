#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>

#include "../controller/controller.h"
#include "credit.h"
#include "deposit.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(QWidget *parent = nullptr);
  ~View();

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
  Ui::View *ui_;
  Credit *credit_;
  Deposit *deposit_;

  std::string str_;
  QPushButton *button_;
  s21::Controller calc_;

  size_t size_ = 0;
  bool is_dot_ = false;
  bool graph_open_ = false;
  const std::array<char, 7> operators_ = {'-', '+', '*', '/', '^', 'd', '('};
};

#endif  // VIEW_H
