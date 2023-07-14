#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include <QDateEdit>
#include <QMessageBox>
#include <QVBoxLayout>

#include "../controller/controller.h"

namespace Ui {
class Credit;
}

class Credit : public QDialog {
  Q_OBJECT

 public:
  explicit Credit(QWidget *parent = nullptr);
  ~Credit();

 private slots:
  void DelRow() noexcept;
  bool DataIsCorrect() noexcept;
  void on_showResult_clicked() noexcept;
  void on_calculator_clicked() noexcept;
  void keyPressEvent(QKeyEvent *event) override;
  void AddRow(const int &term, const QVector<QString> &res_arr,
              const bool &is_annu) noexcept;

 signals:
  void firstWindow();

 private:
  int count_ = 0;
  Ui::Credit *ui_;
  QVBoxLayout *addVbox_;
  s21::Controller calc_;
};

#endif  // CREDITWINDOW_H
