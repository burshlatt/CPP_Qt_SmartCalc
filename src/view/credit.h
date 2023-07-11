#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include "../controller/controller.h"

namespace Ui {
class credit;
}

class credit : public QDialog {
  Q_OBJECT

public:
  explicit credit(QWidget *parent = nullptr);
  ~credit();

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
  Ui::credit *ui;
  QVBoxLayout *addVbox;
  s21::controller calc_;
};

#endif // CREDITWINDOW_H
