#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include <QDateEdit>
#include <QMessageBox>
#include <QVBoxLayout>

#include "../controller/controller_credit.h"

namespace Ui {
class ViewCredit;
}

class ViewCredit : public QDialog {
  Q_OBJECT

 public:
  explicit ViewCredit(QWidget *parent = nullptr);
  ~ViewCredit();

 private slots:
  void DelRow() noexcept;
  bool DataIsCorrect() noexcept;
  void on_showResult_clicked() noexcept;
  void on_calculator_clicked() noexcept;
  void keyPressEvent(QKeyEvent *event) override;
  void AddRow(const int &term, const QVector<QString> &res_arr, const bool &is_annu) noexcept;

 signals:
  void firstWindow();

 private:
  int count_ = 0;
  Ui::ViewCredit *ui_;
  QVBoxLayout *addVbox_;
  s21::ControllerCredit calc_;
};

#endif  // CREDITWINDOW_H
