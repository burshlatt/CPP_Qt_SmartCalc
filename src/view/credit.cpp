#include "credit.h"
#include "ui_credit.h"

credit::credit(QWidget *parent)
    : QDialog(parent), ui(new Ui::credit) {
  ui->setupUi(this);

  this->setFixedSize(480, 325);

  QScreen *screen = QGuiApplication::primaryScreen();
  QRect screenGeometry = screen->geometry();
  int x = (screenGeometry.width() - 480) / 2;
  int y = (screenGeometry.height() - 330) / 2;
  move(x, y);
}

credit::~credit() { delete ui; }

void credit::on_calculator_clicked() {
  this->close();
  emit firstWindow();
}

bool credit::IsCorrect() {
  bool is_correct_ = true;
  QString sum = ui->creditSum->text();
  QString term = ui->creditTerm->text();
  QString percent = ui->percent->text();
  for (int i = 0; i < sum.size(); i++) {
    if ((sum[i] < '0' || sum[i] > '9') && sum[i] != '.') {
      ui->creditSum->setText("ERROR!");
      is_correct_ = false;
      break;
    }
  }
  for (int i = 0; i < term.size(); i++) {
    if (term[i] < '0' || term[i] > '9') {
      ui->creditTerm->setText("ERROR!");
      is_correct_ = false;
      break;
    }
  }
  for (int i = 0; i < percent.size(); i++) {
    if ((percent[i] < '0' || percent[i] > '9') && percent[i] != '.') {
      ui->percent->setText("ERROR!");
      is_correct_ = false;
      break;
    }
  }
  return is_correct_;
}

void credit::on_showResult_clicked() {
  if (IsCorrect()) {
    this->setFixedSize(480, 480);
    ui->monthRes->clear();
    ui->overPay->clear();
    ui->resultSum->clear();
    double *result_ = nullptr;
    double sum_ = ui->creditSum->text().toDouble();
    double percent_ = ui->percent->text().toDouble();
    int term_ = ui->month->isChecked() ? ui->creditTerm->text().toInt() : ui->creditTerm->text().toInt() * 12;
//    ui->monthRes->setText(ui->monthRes->text() + "0");
    if (ui->annu->isChecked()) {
      result_ = calc_.AnnuityCredit(sum_, term_, percent_);
      ui->monthRes->clear();
      ui->monthRes->setText(ui->monthRes->text() + QString::number(result_[2], 'f', 2));
    } else {
      result_ = calc_.DifferentiatedCredit(sum_, term_, percent_);
      ui->monthRes->clear();
      ui->monthRes->setText(ui->monthRes->text() + QString::number(result_[2], 'f', 2) + " ... " + QString::number(result_[3], 'f', 2));
    }
    ui->overPay->setText(ui->overPay->text() + QString::number(result_[0], 'f', 2));
    ui->resultSum->setText(ui->resultSum->text() + QString::number(result_[1], 'f', 2));
    delete[] result_;
    result_ = nullptr;
  }
}
