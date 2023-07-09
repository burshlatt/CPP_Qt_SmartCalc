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

void credit::AddRow(int term, std::vector<double> res_arr, bool is_annu) {
    for (int i = 1; i <= term; i++) {
      QHBoxLayout *hboxLayout = new QHBoxLayout();
      QLabel* id_ = new QLabel(ui->tableScroll->widget());
      QDateEdit* date_ = new QDateEdit(ui->tableScroll->widget());
      QLabel* sum_ = new QLabel(ui->tableScroll->widget());

      id_->setFixedWidth(110);
      id_->setFixedHeight(35);
      hboxLayout->addWidget(id_);

      date_->setReadOnly(true);
      date_->setFixedWidth(110);
      date_->setFixedHeight(35);
      hboxLayout->addWidget(date_);

      sum_->setFixedWidth(110);
      sum_->setFixedHeight(35);
      hboxLayout->addWidget(sum_);

      id_->setText(QString::number(i));

      date_->setDate(QDate::currentDate());
      QDate current_date_ = date_->date();
      date_->setDate(current_date_.addMonths(i - 1));

      is_annu ? sum_->setText(QString::number(res_arr[2], 'f', 2)) : sum_->setText(QString::number(res_arr[i - 1], 'f', 2));

      addVbox->addLayout(hboxLayout);
      count_++;
    }
}

void credit::DelRow() {
  while (count_) {
    QLayout *layout_ = addVbox->itemAt(count_ - 1)->layout();
    QWidget *widget_1_ = layout_->itemAt(0)->widget();
    QWidget *widget_2_ = layout_->itemAt(1)->widget();
    QWidget *widget_3_ = layout_->itemAt(2)->widget();
    delete layout_;
    delete widget_1_;
    delete widget_2_;
    delete widget_3_;
    count_--;
  }
}

void credit::on_showResult_clicked() {
  double sum_ = ui->creditSum->text().toDouble();
  double percent_ = ui->percent->text().toDouble();
  int term_ = ui->month->isChecked() ? ui->creditTerm->text().toInt() : ui->creditTerm->text().toInt() * 12;
  if (term_ > 600) {
      QMessageBox msg_box_;
      msg_box_.setText("Срок должен быть не больше 50 лет (600 месяцев).");
      msg_box_.exec();
  } else {
      if (IsCorrect()) {
        DelRow();
        this->setFixedSize(960, 480);
        ui->monthRes->clear();
        ui->overPay->clear();
        ui->resultSum->clear();
        std::vector<double> result_;
        if (ui->annu->isChecked()) {
          result_ = calc_.AnnuCred(sum_, term_, percent_);
          ui->monthRes->clear();
          ui->monthRes->setText(QString::number(result_[2], 'f', 2));
          AddRow(term_, result_, true);
          ui->overPay->setText(QString::number(result_[0], 'f', 2));
          ui->resultSum->setText(QString::number(result_[1], 'f', 2));
        } else {
          result_ = calc_.DifferCred(sum_, term_, percent_);
          ui->monthRes->clear();
          ui->monthRes->setText(QString::number(result_[0], 'f', 2) + " ... " + QString::number(result_[result_.size() - 3], 'f', 2));
          AddRow(term_, result_, false);
          ui->overPay->setText(QString::number(result_[result_.size() - 2], 'f', 2));
          ui->resultSum->setText(QString::number(result_[result_.size() - 1], 'f', 2));
        }
      }
  }
}
