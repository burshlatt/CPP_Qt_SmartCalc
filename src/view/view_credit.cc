#include "view_credit.h"
#include "ui_view_credit.h"

ViewCredit::ViewCredit(QWidget *parent) : QDialog(parent), ui_(new Ui::ViewCredit) {
  ui_->setupUi(this);

  this->setFixedSize(480, 325);

  QScreen *screen = QGuiApplication::primaryScreen();
  QRect screenGeometry = screen->geometry();
  const int x = (screenGeometry.width() - 480) / 2;
  const int y = (screenGeometry.height() - 330) / 2;
  move(x, y);

  addVbox_ = new QVBoxLayout();
  ui_->tableScroll->widget()->setLayout(addVbox_);
  ui_->tableLayout->addWidget(ui_->tableScroll);

  connect(ui_->calculator, SIGNAL(clicked()), this, SLOT(CalculatorClicked()));
  connect(ui_->showResult, SIGNAL(clicked()), this, SLOT(ShowResultClicked()));
}

ViewCredit::~ViewCredit() { delete ui_; }

void ViewCredit::CalculatorClicked() noexcept {
  this->close();
  emit firstWindow();
}

void ViewCredit::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Escape) {
    event->accept();
    CalculatorClicked();
  }
}

void ViewCredit::AddRow(const int &term, const QVector<QString> &res_arr, const bool &is_annu) noexcept {
  for (int i = 1; i <= term; i++) {
    QHBoxLayout *hboxLayout = new QHBoxLayout();
    QLabel *id_ = new QLabel(ui_->tableScroll->widget());
    QDateEdit *date_ = new QDateEdit(ui_->tableScroll->widget());
    QLabel *sum_ = new QLabel(ui_->tableScroll->widget());

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

    is_annu ? sum_->setText(res_arr[0]) : sum_->setText(res_arr[i]);

    addVbox_->addLayout(hboxLayout);
    count_++;
  }
}

void ViewCredit::DelRow() noexcept {
  while (count_) {
    QLayout *layout_ = addVbox_->itemAt(count_ - 1)->layout();
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

bool ViewCredit::DataIsCorrect() noexcept {
  QString sum_ = ui_->creditSum->text();
  QString term_ = ui_->creditTerm->text();
  QString percent_ = ui_->percent->text();
  if (valid_.IsCorrectInt(term_) && valid_.IsCorrectDec(sum_) && valid_.IsCorrectDec(percent_))
    return true;
  else
    return false;
}

void ViewCredit::ShowResultClicked() noexcept {
  const double sum_ = ui_->creditSum->text().toDouble();
  const int term_ = ui_->month->isChecked() ? ui_->creditTerm->text().toInt() : ui_->creditTerm->text().toInt() * 12;
  if (term_ > 600) {
    QMessageBox msg_box_;
    msg_box_.setText("Срок должен быть не больше 50 лет (600 месяцев).");
    msg_box_.exec();
  } else {
    if (DataIsCorrect()) {
      DelRow();
      this->setFixedSize(960, 480);
      ui_->monthRes->clear();
      ui_->overPay->clear();
      ui_->resultSum->clear();
      QVector<QString> result_;
      calc_.set_sum(sum_);
      calc_.set_term(term_);
      calc_.set_percent(ui_->percent->text());
      if (ui_->annu->isChecked()) {
        result_ = calc_.AnnuCred();
        ui_->overPay->setText(result_[1]);
        ui_->monthRes->setText(result_[0]);
        ui_->resultSum->setText(result_[2]);
        AddRow(term_, result_, true);
      } else {
        result_ = calc_.DifferCred();
        ui_->overPay->setText(result_.back());
        ui_->resultSum->setText(result_.front());
        ui_->monthRes->setText(result_[1] + " ... " +
                               result_[result_.size() - 2]);
        AddRow(term_, result_, false);
      }
    } else {
      QMessageBox msg_box_;
      msg_box_.setText("Вы ввели некорректные данные!");
      msg_box_.exec();
    }
  }
}
