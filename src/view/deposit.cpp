#include "deposit.h"
#include "ui_deposit.h"

deposit::deposit(QWidget *parent)
    : QDialog(parent), ui(new Ui::deposit) {
  ui->setupUi(this);

  this->setFixedSize(1000, 425);

  add_box_ = new QVBoxLayout();
  ui->scrollPayment->widget()->setLayout(add_box_);
  ui->addLayout->addWidget(ui->scrollPayment);

  waste_box_ = new QVBoxLayout();
  ui->scrollWaste->widget()->setLayout(waste_box_);
  ui->wasteLayout->addWidget(ui->scrollWaste);
}

deposit::~deposit() { delete ui; }

void deposit::on_calculator_clicked() noexcept {
  this->close();
  emit firstWindow();
}

void deposit::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        event->accept();
        on_calculator_clicked();
    }
}

void deposit::on_addPayment_clicked() noexcept {
  QHBoxLayout *hboxLayout = new QHBoxLayout();
  QComboBox *addComboBox = new QComboBox(ui->scrollPayment->widget());
  addComboBox->addItem("Разовое");
  addComboBox->addItem("Раз в месяц");
  addComboBox->addItem("Раз в 2 месяца");
  addComboBox->addItem("Раз в квартал");
  addComboBox->addItem("Раз в полгода");
  addComboBox->addItem("Раз в год");
  addComboBox->setFixedWidth(110);
  addComboBox->setFixedHeight(35);
  hboxLayout->addWidget(addComboBox);

  QDateEdit *addDate = new QDateEdit(ui->scrollPayment->widget());
  addDate->setCalendarPopup(true);
  addDate->setFixedWidth(105);
  addDate->setFixedHeight(35);
  hboxLayout->addWidget(addDate);
  addDate->setDate(QDate::currentDate());

  QLineEdit *addLine = new QLineEdit(ui->scrollPayment->widget());
  addLine->setFixedWidth(170);
  addLine->setFixedHeight(35);
  hboxLayout->addWidget(addLine);

  add_box_->addLayout(hboxLayout);

  combo_boxes_add_.append(addComboBox);
  date_edits_add_.append(addDate);
  line_edits_add_.append(addLine);
  add_count_++;
}

void deposit::on_deletePayment_clicked() noexcept {
  if (add_count_) {
    QLayout *layout = add_box_->itemAt(add_count_ - 1)->layout();
    QWidget *widget1 = layout->itemAt(0)->widget();
    QWidget *widget2 = layout->itemAt(1)->widget();
    QWidget *widget3 = layout->itemAt(2)->widget();
    delete layout;
    delete widget1;
    delete widget2;
    delete widget3;
    combo_boxes_add_.removeLast();
    date_edits_add_.removeLast();
    line_edits_add_.removeLast();
    add_count_--;
  }
}

void deposit::on_addWaste_clicked() noexcept {
  QHBoxLayout *hboxLayout = new QHBoxLayout();
  QComboBox *delComboBox = new QComboBox(ui->scrollWaste->widget());
  delComboBox->addItem("Разовое");
  delComboBox->addItem("Раз в месяц");
  delComboBox->addItem("Раз в 2 месяца");
  delComboBox->addItem("Раз в квартал");
  delComboBox->addItem("Раз в полгода");
  delComboBox->addItem("Раз в год");
  delComboBox->setFixedWidth(110);
  delComboBox->setFixedHeight(35);
  hboxLayout->addWidget(delComboBox);

  QDateEdit *delData = new QDateEdit(ui->scrollWaste->widget());
  delData->setCalendarPopup(true);
  delData->setFixedWidth(105);
  delData->setFixedHeight(35);
  hboxLayout->addWidget(delData);
  delData->setDate(QDate::currentDate());

  QLineEdit *delLine = new QLineEdit(ui->scrollWaste->widget());
  delLine->setFixedWidth(170);
  delLine->setFixedHeight(35);
  hboxLayout->addWidget(delLine);

  waste_box_->addLayout(hboxLayout);

  combo_boxes_waste_.append(delComboBox);
  date_edits_waste_.append(delData);
  line_edits_waste_.append(delLine);
  waste_count_++;
}

void deposit::on_deleteWaste_clicked() noexcept {
  if (waste_count_) {
    QLayout *layout = waste_box_->itemAt(waste_count_ - 1)->layout();
    QWidget *widget1 = layout->itemAt(0)->widget();
    QWidget *widget2 = layout->itemAt(1)->widget();
    QWidget *widget3 = layout->itemAt(2)->widget();
    delete layout;
    delete widget1;
    delete widget2;
    delete widget3;
    combo_boxes_waste_.removeLast();
    date_edits_waste_.removeLast();
    line_edits_waste_.removeLast();
    waste_count_--;
  }
}

void deposit::add_payment() noexcept {
    add_sum_ = 0.0;
    for (int i = 0; i < add_count_; i++) {
      QDate date_add = date_edits_add_[i]->date();
      QString text_add = line_edits_add_[i]->text();
      QString combobox_add = combo_boxes_add_[i]->currentText();
      int diff_time_ = (last_date_.year() - date_edits_add_[i]->date().year()) * 12 + last_date_.month() - date_edits_add_[i]->date().month();
      if (calc_.IsCorrectDec(text_add)) {
        if (date_add <= last_date_) {
          if (combobox_add == "Разовое") {
            if (date_add >= QDate::currentDate()) {
              add_sum_ += text_add.toDouble();
            }
          } else if (combobox_add == "Раз в месяц") {
            add_sum_ += calc_.AddSum(text_add.toDouble(), diff_time_);
          } else if (combobox_add == "Раз в 2 месяца") {
            add_sum_ += calc_.AddSum(text_add.toDouble(), (int)(diff_time_ / 2));
          } else if (combobox_add == "Раз в квартал") {
            add_sum_ += calc_.AddSum(text_add.toDouble(), (int)(diff_time_ / 3));
          } else if (combobox_add == "Раз в полгода") {
            add_sum_ += calc_.AddSum(text_add.toDouble(), (int)(diff_time_ / 6));
          } else if (combobox_add == "Раз в год") {
            add_sum_ += calc_.AddSum(text_add.toDouble(), (int)(diff_time_ / 12));
          }
        }
      } else {
        line_edits_add_[i]->setText("ERROR!");
      }
    }
}

void deposit::add_waste() noexcept {
    waste_sum_ = 0.0;
    for (int i = 0; i < waste_count_; i++) {
      QDate date_waste = date_edits_waste_[i]->date();
      QString text_waste = line_edits_waste_[i]->text();
      QString combobox_waste = combo_boxes_waste_[i]->currentText();
      int diff_time_ = (last_date_.year() - date_edits_add_[i]->date().year()) * 12 + last_date_.month() - date_edits_add_[i]->date().month();
      if (calc_.IsCorrectDec(text_waste)) {
        if (date_waste <= last_date_) {
          if (combobox_waste == "Разовое") {
            if (date_waste >= QDate::currentDate()) {
              waste_sum_ += text_waste.toDouble();
            }
          } else if (combobox_waste == "Раз в месяц") {
            waste_sum_ += calc_.AddSum(text_waste.toDouble(), diff_time_);
          } else if (combobox_waste == "Раз в 2 месяца") {
            waste_sum_ += calc_.AddSum(text_waste.toDouble(), (int)(diff_time_ / 2));
          } else if (combobox_waste == "Раз в квартал") {
            waste_sum_ += calc_.AddSum(text_waste.toDouble(), (int)(diff_time_ / 3));
          } else if (combobox_waste == "Раз в полгода") {
            waste_sum_ += calc_.AddSum(text_waste.toDouble(), (int)(diff_time_ / 6));
          } else if (combobox_waste == "Раз в год") {
            waste_sum_ += calc_.AddSum(text_waste.toDouble(), (int)(diff_time_ / 12));
          }
        }
      } else {
        line_edits_waste_[i]->setText("ERROR!");
      }
    }
}

void deposit::CheckTypes() noexcept {
  if (ui->yes->isChecked()) {
    is_cap_ = true;
  } else if (ui->no->isChecked()) {
    is_cap_ = false;
  }
  if (ui->day->isChecked()) {
    time_type_ = 1;
  } else if (ui->month->isChecked()) {
    time_type_ = 2;
  } else if (ui->year->isChecked()) {
    time_type_ = 3;
  }
  if (ui->periodCombo->currentText() == "Каждый день") {
    period_ = 1;
  } else if (ui->periodCombo->currentText() == "Каждую неделю") {
    period_ = 2;
  } else if (ui->periodCombo->currentText() == "Раз в месяц") {
    period_ = 3;
  } else if (ui->periodCombo->currentText() == "Раз в квартал") {
    period_ = 4;
  } else if (ui->periodCombo->currentText() == "Раз в полгода") {
    period_ = 5;
  } else if (ui->periodCombo->currentText() == "Раз в год") {
    period_ = 6;
  } else if (ui->periodCombo->currentText() == "В конце срока") {
    period_ = 7;
  }
}

bool deposit::DataIsCorrect() noexcept {
    if (calc_.IsCorrectDec(sum_) && calc_.IsCorrectDec(percent_) &&
        calc_.IsCorrectDec(tax_rate_) && calc_.IsCorrectInt(term_))
        return true;
    else
        return false;
}

void deposit::on_showResult_clicked() noexcept {
  term_ = ui->time->text();
  percent_ = ui->percent->text();
  tax_rate_ = ui->taxRate->text();
  sum_ = ui->depositAmount->text();
  if (DataIsCorrect()) {
    this->setFixedSize(1000, 520);
    ui->tax->clear();
    ui->resultSum->clear();
    ui->resultProfit->clear();
    ui->resultPercent->clear();

    int time_ = ui->time->text().toInt();
    CheckTypes();
    if (time_type_ == 1) last_date_ = QDate::currentDate().addDays(time_);
    else if (time_type_ == 2) last_date_ = QDate::currentDate().addMonths(time_);
    else if (time_type_ == 3) last_date_ = QDate::currentDate().addYears(time_);

    add_payment();
    add_waste();

    calc_.set_sum(sum_.toDouble() + add_sum_ - waste_sum_);
    calc_.set_term(QDate::currentDate().daysTo(last_date_));
    calc_.set_cap(is_cap_);
    calc_.set_percent(percent_);
    calc_.set_period(period_);
    calc_.set_tax(tax_rate_);

    QVector<QString> result_ = calc_.Deposit();

    ui->tax->setText(result_[2]);
    ui->resultSum->setText(result_[0]);
    ui->resultProfit->setText(result_[3]);
    ui->resultPercent->setText(result_[1]);
  } else {
      QMessageBox msg_box_;
      msg_box_.setText("Вы ввели некорректные данные!");
      msg_box_.exec();
  }
}
