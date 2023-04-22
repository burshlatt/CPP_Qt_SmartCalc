#include "depositwindow.h"
#include "ui_depositwindow.h"

DepositWindow::DepositWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::DepositWindow) {
  ui->setupUi(this);

  this->setFixedSize(1000, 425);

  ui->periodCombo->addItem("Каждый день");
  ui->periodCombo->addItem("Каждую неделю");
  ui->periodCombo->addItem("Раз в месяц");
  ui->periodCombo->addItem("Раз в квартал");
  ui->periodCombo->addItem("Раз в полгода");
  ui->periodCombo->addItem("Раз в год");
  ui->periodCombo->addItem("В конце срока");

  addVbox = new QVBoxLayout();
  ui->scrollPayment->widget()->setLayout(addVbox);
  ui->addLayout->addWidget(ui->scrollPayment);

  wasteVbox = new QVBoxLayout();
  ui->scrollWaste->widget()->setLayout(wasteVbox);
  ui->wasteLayout->addWidget(ui->scrollWaste);
}

DepositWindow::~DepositWindow() { delete ui; }

void DepositWindow::on_calculator_clicked() {
  this->close();
  emit firstWindow();
}

void DepositWindow::today_is() {
  char *date_char = current_date();
  std::string date_string = std::string(date_char);
  free_array(date_char);
  QString date_qstring = QString::fromStdString(date_string);
  date_qdate = QDate::fromString(date_qstring, "dd/MM/yyyy");
}

void DepositWindow::on_addPayment_clicked() {
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
  today_is();
  addDate->setDate(date_qdate);

  QLineEdit *addLine = new QLineEdit(ui->scrollPayment->widget());
  addLine->setFixedWidth(200);
  addLine->setFixedHeight(35);
  hboxLayout->addWidget(addLine);

  addVbox->addLayout(hboxLayout);

  comboBoxesAdd.append(addComboBox);
  dateEditsAdd.append(addDate);
  lineEditsAdd.append(addLine);
  count_of_elem_add++;
}

void DepositWindow::on_deletePayment_clicked() {
  if (count_of_elem_add > 0) {
    QLayout *layout = addVbox->itemAt(count_of_elem_add - 1)->layout();
    QWidget *widget1 = layout->itemAt(0)->widget();
    QWidget *widget2 = layout->itemAt(1)->widget();
    QWidget *widget3 = layout->itemAt(2)->widget();
    delete layout;
    delete widget1;
    delete widget2;
    delete widget3;
    comboBoxesAdd.removeLast();
    dateEditsAdd.removeLast();
    lineEditsAdd.removeLast();
    count_of_elem_add--;
  }
}

void DepositWindow::on_addWaste_clicked() {
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
  today_is();
  delData->setDate(date_qdate);

  QLineEdit *delLine = new QLineEdit(ui->scrollWaste->widget());
  delLine->setFixedWidth(200);
  delLine->setFixedHeight(35);
  hboxLayout->addWidget(delLine);

  wasteVbox->addLayout(hboxLayout);

  comboBoxesWaste.append(delComboBox);
  dateEditsWaste.append(delData);
  lineEditsWaste.append(delLine);
  count_of_elem_waste++;
}

void DepositWindow::on_deleteWaste_clicked() {
  if (count_of_elem_waste > 0) {
    QLayout *layout = wasteVbox->itemAt(count_of_elem_waste - 1)->layout();
    QWidget *widget1 = layout->itemAt(0)->widget();
    QWidget *widget2 = layout->itemAt(1)->widget();
    QWidget *widget3 = layout->itemAt(2)->widget();
    delete layout;
    delete widget1;
    delete widget2;
    delete widget3;
    comboBoxesWaste.removeLast();
    dateEditsWaste.removeLast();
    lineEditsWaste.removeLast();
    count_of_elem_waste--;
  }
}

void DepositWindow::check_correct_sum(QString sum) {
  error_dop = 0;
  for (int i = 0; i < sum.size(); i++) {
    if ((sum[i] < '0' || sum[i] > '9') && sum[i] != '.') {
      error_dop = 1;
    }
  }
}

void DepositWindow::additional_payment(double *add_sum) {
  if (comboBoxesAdd.size() > 0 && dateEditsAdd.size() > 0 &&
      lineEditsAdd.size() > 0) {
    for (int i = 0; i < count_of_elem_add; i++) {
      QDate date_add = dateEditsAdd[i]->date();
      QString text_add = lineEditsAdd[i]->text();
      QString combobox_add = comboBoxesAdd[i]->currentText();
      std::string date_stdstr = dateEditsAdd[i]->text().toStdString();
      char *date_intermediate = &date_stdstr[0];
      int converted_time = date_difference(date_end, date_intermediate);
      check_correct_sum(text_add);
      if (!error_dop) {
        if (date_add <= date_qdate_max) {
          if (combobox_add == "Разовое") {
            if (date_add >= date_qdate) {
              *add_sum += text_add.toDouble();
            }
          } else if (combobox_add == "Раз в месяц") {
            *add_sum += add_start_sum(text_add.toDouble(), converted_time, 1);
          } else if (combobox_add == "Раз в 2 месяца") {
            *add_sum += add_start_sum(text_add.toDouble(), converted_time, 2);
          } else if (combobox_add == "Раз в квартал") {
            *add_sum += add_start_sum(text_add.toDouble(), converted_time, 3);
          } else if (combobox_add == "Раз в полгода") {
            *add_sum += add_start_sum(text_add.toDouble(), converted_time, 4);
          } else if (combobox_add == "Раз в год") {
            *add_sum += add_start_sum(text_add.toDouble(), converted_time, 5);
          }
        }
      } else {
        lineEditsAdd[i]->setText("ERROR!");
      }
    }
  }
}

void DepositWindow::additional_waste(double *waste_sum) {
  if (comboBoxesWaste.size() > 0 && dateEditsWaste.size() > 0 &&
      lineEditsWaste.size() > 0) {
    for (int i = 0; i < count_of_elem_waste; i++) {
      QDate date_waste = dateEditsWaste[i]->date();
      QString text_waste = lineEditsWaste[i]->text();
      QString combobox_waste = comboBoxesWaste[i]->currentText();
      std::string date_stdstr = dateEditsWaste[i]->text().toStdString();
      char *date_intermediate = &date_stdstr[0];
      int converted_time = date_difference(date_end, date_intermediate);
      check_correct_sum(text_waste);
      if (!error_dop) {
        if (date_waste <= date_qdate_max) {
          if (combobox_waste == "Разовое") {
            if (date_waste >= date_qdate) {
              *waste_sum += text_waste.toDouble();
            }
          } else if (combobox_waste == "Раз в месяц") {
            *waste_sum +=
                add_start_sum(text_waste.toDouble(), converted_time, 1);
          } else if (combobox_waste == "Раз в 2 месяца") {
            *waste_sum +=
                add_start_sum(text_waste.toDouble(), converted_time, 2);
          } else if (combobox_waste == "Раз в квартал") {
            *waste_sum +=
                add_start_sum(text_waste.toDouble(), converted_time, 3);
          } else if (combobox_waste == "Раз в полгода") {
            *waste_sum +=
                add_start_sum(text_waste.toDouble(), converted_time, 4);
          } else if (combobox_waste == "Раз в год") {
            *waste_sum +=
                add_start_sum(text_waste.toDouble(), converted_time, 5);
          }
        }
      } else {
        lineEditsWaste[i]->setText("ERROR!");
      }
    }
  }
}

void DepositWindow::check_types() {
  if (ui->yes->isChecked()) {
    capitalization = 1;
  } else if (ui->no->isChecked()) {
    capitalization = 0;
  }
  if (ui->day->isChecked()) {
    time_type = 1;
  } else if (ui->month->isChecked()) {
    time_type = 2;
  } else if (ui->year->isChecked()) {
    time_type = 3;
  }
  if (ui->periodCombo->currentText() == "Каждый день") {
    period_type = 1;
  } else if (ui->periodCombo->currentText() == "Каждую неделю") {
    period_type = 2;
  } else if (ui->periodCombo->currentText() == "Раз в месяц") {
    period_type = 3;
  } else if (ui->periodCombo->currentText() == "Раз в квартал") {
    period_type = 4;
  } else if (ui->periodCombo->currentText() == "Раз в полгода") {
    period_type = 5;
  } else if (ui->periodCombo->currentText() == "Раз в год") {
    period_type = 6;
  } else if (ui->periodCombo->currentText() == "В конце срока") {
    period_type = 7;
  }
}

void DepositWindow::check_correct_data() {
  error = 0;
  QString term = ui->time->text();
  QString percent = ui->percent->text();
  QString tax_rate = ui->taxRate->text();
  QString sum = ui->depositAmount->text();
  for (int i = 0; i < sum.size(); i++) {
    if ((sum[i] < '0' || sum[i] > '9') && sum[i] != '.') {
      error = 1;
    }
  }
  if (error == 1) {
    ui->depositAmount->setText("ERROR!");
  }
  for (int i = 0; i < term.size(); i++) {
    if (term[i] < '0' || term[i] > '9') {
      error = 2;
    }
  }
  if (error == 2) {
    ui->time->setText("ERROR!");
  }
  for (int i = 0; i < percent.size(); i++) {
    if ((percent[i] < '0' || percent[i] > '9') && percent[i] != '.') {
      error = 3;
    }
  }
  if (error == 3) {
    ui->percent->setText("ERROR!");
  }
  for (int i = 0; i < tax_rate.size(); i++) {
    if ((tax_rate[i] < '0' || tax_rate[i] > '9') && tax_rate[i] != '.') {
      error = 4;
    }
  }
  if (error == 4) {
    ui->taxRate->setText("ERROR!");
  }
}

void DepositWindow::on_showResult_clicked() {
  check_correct_data();
  if (error == 0) {
    this->setFixedSize(1000, 520);
    ui->tax->clear();
    ui->resultSum->clear();
    ui->resultProfit->clear();
    ui->resultPercent->clear();
    double add_sum = 0.0;
    double waste_sum = 0.0;
    double sum_result = 0.0;
    double tax_result = 0.0;
    double profit_result = 0.0;
    double percent_result = 0.0;
    double percent = ui->percent->text().toDouble();
    double tax_rate = ui->taxRate->text().toDouble();
    double sum = ui->depositAmount->text().toDouble();
    int time = ui->time->text().toInt();
    check_types();
    char *today = current_date();
    date_end = end_date(today, time, time_type);
    std::string date_string = std::string(date_end);
    QString date_qstring = QString::fromStdString(date_string);
    date_qdate_max = QDate::fromString(date_qstring, "dd/MM/yyyy");
    today_is();
    additional_payment(&add_sum);
    additional_waste(&waste_sum);
    deposit_calculator(sum + add_sum - waste_sum, time, time_type, percent,
                       tax_rate, period_type, capitalization, &percent_result,
                       &tax_result, &profit_result, &sum_result);
    ui->tax->setText(ui->resultPercent->text() +
                     QString::number(tax_result, 'f', 2));
    ui->resultSum->setText(ui->resultPercent->text() +
                           QString::number(sum_result, 'f', 2));
    ui->resultProfit->setText(ui->resultPercent->text() +
                              QString::number(profit_result, 'f', 2));
    ui->resultPercent->setText(ui->resultPercent->text() +
                               QString::number(percent_result, 'f', 2));
    free_array(today);
    free_array(date_end);
  }
}
