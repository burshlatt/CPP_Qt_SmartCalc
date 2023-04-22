#include "creditwindow.h"
#include "ui_creditwindow.h"

CreditWindow::CreditWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::CreditWindow) {
  ui->setupUi(this);

  this->setFixedSize(480, 325);

  QScreen *screen = QGuiApplication::primaryScreen();
  QRect screenGeometry = screen->geometry();
  int x = (screenGeometry.width() - 480) / 2;
  int y = (screenGeometry.height() - 330) / 2;
  move(x, y);
}

CreditWindow::~CreditWindow() { delete ui; }

void CreditWindow::on_calculator_clicked() {
  this->close();
  emit firstWindow();
}

void CreditWindow::check_correct_data() {
  error = 0;
  QString sum = ui->creditSum->text();
  QString term = ui->creditTerm->text();
  QString percent = ui->percent->text();
  for (int i = 0; i < sum.size(); i++) {
    if ((sum[i] < '0' || sum[i] > '9') && sum[i] != '.') {
      error = 1;
    }
  }
  if (error == 1) {
    ui->creditSum->setText("ERROR!");
  }
  for (int i = 0; i < term.size(); i++) {
    if (term[i] < '0' || term[i] > '9') {
      error = 2;
    }
  }
  if (error == 2) {
    ui->creditTerm->setText("ERROR!");
  }
  for (int i = 0; i < percent.size(); i++) {
    if ((percent[i] < '0' || percent[i] > '9') && percent[i] != '.') {
      error = 3;
    }
  }
  if (error == 3) {
    ui->percent->setText("ERROR!");
  }
}

void CreditWindow::on_showResult_clicked() {
  check_correct_data();
  if (!error) {
    this->setFixedSize(480, 480);
    ui->monthRes->clear();
    ui->overPay->clear();
    ui->resultSum->clear();
    double all_sum = 0.0;
    double over_pay = 0.0;
    double month_payment = 0.0;
    double last_payment = 0.0;
    double first_payment = 0.0;
    int termCred = ui->creditTerm->text().toInt();
    double sumCred = ui->creditSum->text().toDouble();
    double percentCred = ui->percent->text().toDouble();
    check_correct_data();
    ui->monthRes->setText(ui->monthRes->text() + "0");
    if (ui->annu->isChecked()) {
      if (ui->month->isChecked()) {
        all_sum = annuity_credit(sumCred, termCred, 1, percentCred,
                                 &month_payment, &over_pay);
      }
      if (ui->year->isChecked()) {
        all_sum = annuity_credit(sumCred, termCred, 2, percentCred,
                                 &month_payment, &over_pay);
      }
      ui->monthRes->clear();
      ui->monthRes->setText(ui->monthRes->text() +
                            QString::number(month_payment, 'f', 2));
    }
    if (ui->differ->isChecked()) {
      if (ui->month->isChecked()) {
        all_sum =
            differentiated_credit(sumCred, termCred, 1, percentCred,
                                  &first_payment, &last_payment, &over_pay);
      }
      if (ui->year->isChecked()) {
        all_sum =
            differentiated_credit(sumCred, termCred, 2, percentCred,
                                  &first_payment, &last_payment, &over_pay);
      }
      ui->monthRes->clear();
      ui->monthRes->setText(ui->monthRes->text() +
                            QString::number(first_payment, 'f', 2) + " ... " +
                            QString::number(last_payment, 'f', 2));
    }
    ui->overPay->setText(ui->overPay->text() +
                         QString::number(over_pay, 'f', 2));
    ui->resultSum->setText(ui->resultSum->text() +
                           QString::number(all_sum, 'f', 2));
  }
}
