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

  addVbox = new QVBoxLayout();
  ui->tableScroll->widget()->setLayout(addVbox);
  ui->tableLayout->addWidget(ui->tableScroll);
}

credit::~credit() { delete ui; }

void credit::on_calculator_clicked() {
  this->close();
  emit firstWindow();
}

bool credit::IsCorrect() {
  bool is_correct_ = true;
  QString sum_ = ui->creditSum->text();
  QString term_ = ui->creditTerm->text();
  QString percent_ = ui->percent->text();
  for (int i = 0; i < sum_.size(); i++) {
    if ((sum_[i] < '0' || sum_[i] > '9') && sum_[i] != '.') {
      ui->creditSum->setText("ERROR!");
      is_correct_ = false;
      break;
    }
  }
  for (int i = 0; i < term_.size(); i++) {
    if (term_[i] < '0' || term_[i] > '9') {
      ui->creditTerm->setText("ERROR!");
      is_correct_ = false;
      break;
    }
  }
  for (int i = 0; i < percent_.size(); i++) {
    if ((percent_[i] < '0' || percent_[i] > '9') && percent_[i] != '.') {
      ui->percent->setText("ERROR!");
      is_correct_ = false;
      break;
    }
  }
  if (!sum_.size() || !term_.size() || !percent_.size()) is_correct_ = false;
  return is_correct_;
}

void credit::AddRow(QString str) {
  QVector<QLabel *> labels_;
  QHBoxLayout *hboxLayout = new QHBoxLayout();
  QLabel* label_table_1 = new QLabel(ui->tableScroll->widget());
  QLabel* label_table_2 = new QLabel(ui->tableScroll->widget());
  QLabel* label_table_3 = new QLabel(ui->tableScroll->widget());
  QLabel* label_table_4 = new QLabel(ui->tableScroll->widget());
  labels_.push_back(label_table_1);
  labels_.push_back(label_table_2);
  labels_.push_back(label_table_3);
  labels_.push_back(label_table_4);
  for (int i = 0; i < 4; i++) {
    labels_[i]->setFixedWidth(110);
    labels_[i]->setFixedHeight(35);
    hboxLayout->addWidget(labels_[i]);
  }
  labels_[0]->setText(str);
  labels_[1]->setText(str);
  labels_[2]->setText(str);
  labels_[3]->setText(str);
  addVbox->addLayout(hboxLayout);
  count++;
}

void credit::DelRow() {
  if (count > 0) {
//    QLayout *layout = addVbox->itemAt(count_of_elem_add - 1)->layout();
//    QWidget *widget1 = layout->itemAt(0)->widget();
//    QWidget *widget2 = layout->itemAt(1)->widget();
//    QWidget *widget3 = layout->itemAt(2)->widget();
//    delete labels_[0];
//    delete labels_[1];
//    delete labels_[2];
//    delete labels_[3];
//    labels_[0] = nullptr;
//    labels_[1] = nullptr;
//    labels_[2] = nullptr;
//    labels_[3] = nullptr;
//    labels_.pop_back();
//    labels_.pop_back();
//    labels_.pop_back();
//    labels_.pop_back();
    count--;
  }
}

void credit::on_showResult_clicked() {
  if (IsCorrect()) {
    DelRow();
    this->setFixedSize(960, 480);
    ui->monthRes->clear();
    ui->overPay->clear();
    ui->resultSum->clear();
    double *result_ = nullptr;
    double sum_ = ui->creditSum->text().toDouble();
    double percent_ = ui->percent->text().toDouble();
    int term_ = ui->month->isChecked() ? ui->creditTerm->text().toInt() : ui->creditTerm->text().toInt() * 12;
    if (ui->annu->isChecked()) {
      result_ = calc_.AnnuCred(sum_, term_, percent_);
      ui->monthRes->clear();
      ui->monthRes->setText(QString::number(result_[2], 'f', 2));
    } else {
      result_ = calc_.DifferCred(sum_, term_, percent_);
      ui->monthRes->clear();
      ui->monthRes->setText(QString::number(result_[2], 'f', 2) + " ... " + QString::number(result_[3], 'f', 2));
    }
    ui->overPay->setText(QString::number(result_[0], 'f', 2));
    ui->resultSum->setText(QString::number(result_[1], 'f', 2));
    delete[] result_;
    result_ = nullptr;
//    QString str[4]{};
    for (int i = 1; i <= term_; i++) {
        AddRow(QString::number(i));
    }
  }
}
