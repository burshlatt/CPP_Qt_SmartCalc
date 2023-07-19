#include "view_deposit.h"
#include "ui_view_deposit.h"

ViewDeposit::ViewDeposit(QWidget *parent) : QDialog(parent), ui_(new Ui::ViewDeposit) {
  ui_->setupUi(this);

  this->setFixedSize(1000, 425);

  add_box_ = new QVBoxLayout();
  ui_->scrollPayment->widget()->setLayout(add_box_);
  ui_->addLayout->addWidget(ui_->scrollPayment);

  waste_box_ = new QVBoxLayout();
  ui_->scrollWaste->widget()->setLayout(waste_box_);
  ui_->wasteLayout->addWidget(ui_->scrollWaste);

  connect(ui_->addWaste, SIGNAL(clicked()), this, SLOT(AddWasteClicked()));
  connect(ui_->calculator, SIGNAL(clicked()), this, SLOT(CalculatorClicked()));
  connect(ui_->showResult, SIGNAL(clicked()), this, SLOT(ShowResultClicked()));
  connect(ui_->addPayment, SIGNAL(clicked()), this, SLOT(AddPaymentClicked()));
  connect(ui_->deleteWaste, SIGNAL(clicked()), this, SLOT(DeleteWasteClicked()));
  connect(ui_->deletePayment, SIGNAL(clicked()), this, SLOT(DeletePaymentClicked()));
}

ViewDeposit::~ViewDeposit() { delete ui_; }

void ViewDeposit::CalculatorClicked() noexcept {
  this->close();
  emit firstWindow();
}

void ViewDeposit::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Escape) {
    event->accept();
    CalculatorClicked();
  }
}

void ViewDeposit::AddPaymentClicked() noexcept {
  QHBoxLayout *hboxLayout = new QHBoxLayout();
  QComboBox *addComboBox = new QComboBox(ui_->scrollPayment->widget());
  addComboBox->addItem("Разовое");
  addComboBox->addItem("Раз в месяц");
  addComboBox->addItem("Раз в 2 месяца");
  addComboBox->addItem("Раз в квартал");
  addComboBox->addItem("Раз в полгода");
  addComboBox->addItem("Раз в год");
  addComboBox->setFixedWidth(110);
  addComboBox->setFixedHeight(35);
  hboxLayout->addWidget(addComboBox);

  QDateEdit *addDate = new QDateEdit(ui_->scrollPayment->widget());
  addDate->setCalendarPopup(true);
  addDate->setFixedWidth(105);
  addDate->setFixedHeight(35);
  hboxLayout->addWidget(addDate);
  addDate->setDate(QDate::currentDate());

  QLineEdit *addLine = new QLineEdit(ui_->scrollPayment->widget());
  addLine->setFixedWidth(170);
  addLine->setFixedHeight(35);
  hboxLayout->addWidget(addLine);

  add_box_->addLayout(hboxLayout);

  combo_boxes_add_.append(addComboBox);
  date_edits_add_.append(addDate);
  line_edits_add_.append(addLine);
  add_count_++;
}

void ViewDeposit::DeletePaymentClicked() noexcept {
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

void ViewDeposit::AddWasteClicked() noexcept {
  QHBoxLayout *hboxLayout = new QHBoxLayout();
  QComboBox *delComboBox = new QComboBox(ui_->scrollWaste->widget());
  delComboBox->addItem("Разовое");
  delComboBox->addItem("Раз в месяц");
  delComboBox->addItem("Раз в 2 месяца");
  delComboBox->addItem("Раз в квартал");
  delComboBox->addItem("Раз в полгода");
  delComboBox->addItem("Раз в год");
  delComboBox->setFixedWidth(110);
  delComboBox->setFixedHeight(35);
  hboxLayout->addWidget(delComboBox);

  QDateEdit *delData = new QDateEdit(ui_->scrollWaste->widget());
  delData->setCalendarPopup(true);
  delData->setFixedWidth(105);
  delData->setFixedHeight(35);
  hboxLayout->addWidget(delData);
  delData->setDate(QDate::currentDate());

  QLineEdit *delLine = new QLineEdit(ui_->scrollWaste->widget());
  delLine->setFixedWidth(170);
  delLine->setFixedHeight(35);
  hboxLayout->addWidget(delLine);

  waste_box_->addLayout(hboxLayout);

  combo_boxes_waste_.append(delComboBox);
  date_edits_waste_.append(delData);
  line_edits_waste_.append(delLine);
  waste_count_++;
}

void ViewDeposit::DeleteWasteClicked() noexcept {
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

void ViewDeposit::AddPayment() noexcept {
  add_sum_ = 0.0;
  for (int i = 0; i < add_count_; i++) {
    QDate date_add = date_edits_add_[i]->date();
    QString text_add = line_edits_add_[i]->text();
    QString combobox_add = combo_boxes_add_[i]->currentText();
    if (valid_.IsCorrectDec(text_add)) {
      if (date_add <= last_date_) {
        add_.push_back(text_add);
        add_days_.push_back(QDate::currentDate().daysTo(date_add));
        if (combobox_add == "Разовое") {
          add_period_.push_back(1);
        } else if (combobox_add == "Раз в месяц") {
          add_period_.push_back(2);
        } else if (combobox_add == "Раз в 2 месяца") {
          add_period_.push_back(3);
        } else if (combobox_add == "Раз в квартал") {
          add_period_.push_back(4);
        } else if (combobox_add == "Раз в полгода") {
          add_period_.push_back(5);
        } else if (combobox_add == "Раз в год") {
          add_period_.push_back(6);
        }
      }
    } else {
      line_edits_add_[i]->setText("ERROR!");
    }
  }
}

void ViewDeposit::AddWaste() noexcept {
  waste_sum_ = 0.0;
  for (int i = 0; i < waste_count_; i++) {
    QDate date_waste = date_edits_waste_[i]->date();
    QString text_waste = line_edits_waste_[i]->text();
    QString combobox_waste = combo_boxes_waste_[i]->currentText();
    if (valid_.IsCorrectDec(text_waste)) {
      if (date_waste <= last_date_) {
        waste_.push_back(text_waste);
        waste_days_.push_back(QDate::currentDate().daysTo(date_waste));
        if (combobox_waste == "Разовое") {
          waste_period_.push_back(1);
        } else if (combobox_waste == "Раз в месяц") {
          waste_period_.push_back(2);
        } else if (combobox_waste == "Раз в 2 месяца") {
          waste_period_.push_back(3);
        } else if (combobox_waste == "Раз в квартал") {
          waste_period_.push_back(4);
        } else if (combobox_waste == "Раз в полгода") {
          waste_period_.push_back(5);
        } else if (combobox_waste == "Раз в год") {
          waste_period_.push_back(6);
        }
      }
    } else {
      line_edits_waste_[i]->setText("ERROR!");
    }
  }
}

void ViewDeposit::CheckTypes() noexcept {
  if (ui_->yes->isChecked()) {
    is_cap_ = true;
  } else if (ui_->no->isChecked()) {
    is_cap_ = false;
  }
  if (ui_->day->isChecked()) {
    time_type_ = 1;
  } else if (ui_->month->isChecked()) {
    time_type_ = 2;
  } else if (ui_->year->isChecked()) {
    time_type_ = 3;
  }
  if (ui_->periodCombo->currentText() == "Каждый день") {
    period_ = 1;
  } else if (ui_->periodCombo->currentText() == "Каждую неделю") {
    period_ = 2;
  } else if (ui_->periodCombo->currentText() == "Раз в месяц") {
    period_ = 3;
  } else if (ui_->periodCombo->currentText() == "Раз в квартал") {
    period_ = 4;
  } else if (ui_->periodCombo->currentText() == "Раз в полгода") {
    period_ = 5;
  } else if (ui_->periodCombo->currentText() == "Раз в год") {
    period_ = 6;
  } else if (ui_->periodCombo->currentText() == "В конце срока") {
    period_ = 7;
  }
}

bool ViewDeposit::DataIsCorrect() noexcept {
  if (valid_.IsCorrectDec(sum_) && valid_.IsCorrectDec(percent_) &&
      valid_.IsCorrectDec(tax_rate_) && valid_.IsCorrectInt(term_))
    return true;
  else
    return false;
}

void ViewDeposit::ShowResultClicked() noexcept {
  term_ = ui_->time->text();
  percent_ = ui_->percent->text();
  tax_rate_ = ui_->taxRate->text();
  sum_ = ui_->depositAmount->text();
  if (DataIsCorrect()) {
    this->setFixedSize(1000, 520);
    ui_->tax->clear();
    ui_->resultSum->clear();
    ui_->resultProfit->clear();
    ui_->resultPercent->clear();
    add_.clear();
    waste_.clear();
    add_period_.clear();
    waste_period_.clear();
    add_days_.clear();
    waste_days_.clear();

    int time_ = ui_->time->text().toInt();
    CheckTypes();
    if (time_type_ == 1) {
      last_date_ = QDate::currentDate().addDays(time_);
    } else if (time_type_ == 2) {
      last_date_ = QDate::currentDate().addMonths(time_);
      time_ *= 30;
    } else if (time_type_ == 3) {
      last_date_ = QDate::currentDate().addYears(time_);
      time_ *= 365;
    }

    AddPayment();
    AddWaste();

    calc_.set_sum(sum_.toDouble());
    calc_.set_cap(is_cap_);
    calc_.set_period(period_);
    calc_.set_percent(percent_);
    calc_.set_tax(tax_rate_);
    calc_.set_term(time_);
    calc_.set_add(add_);
    calc_.set_waste(waste_);
    calc_.set_period_add(add_period_);
    calc_.set_period_waste(waste_period_);
    calc_.set_add_days(add_days_);
    calc_.set_waste_days(waste_days_);

    QVector<QString> result_ = calc_.Deposit();

    ui_->tax->setText(result_[1]);
    ui_->resultSum->setText(result_[3]);
    ui_->resultProfit->setText(result_[2]);
    ui_->resultPercent->setText(result_[0]);
  } else {
    QMessageBox msg_box_;
    msg_box_.setText("Вы ввели некорректные данные!");
    msg_box_.exec();
  }
}
