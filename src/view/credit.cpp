#include "credit.h"
#include "ui_credit.h"

credit::credit(QWidget *parent)
    : QDialog(parent), ui(new Ui::credit) {
  ui->setupUi(this);

  this->setFixedSize(480, 325);

  QScreen *screen = QGuiApplication::primaryScreen();
  QRect screenGeometry = screen->geometry();
  const int x = (screenGeometry.width() - 480) / 2;
  const int y = (screenGeometry.height() - 330) / 2;
  move(x, y);

  addVbox = new QVBoxLayout();
  ui->tableScroll->widget()->setLayout(addVbox);
  ui->tableLayout->addWidget(ui->tableScroll);
}

credit::~credit() { delete ui; }

void credit::on_calculator_clicked() noexcept {
  this->close();
  emit firstWindow();
}

void credit::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        event->accept();
        on_calculator_clicked();
    }
}

void credit::AddRow(const int &term, const QVector<QString> &res_arr, const bool &is_annu) noexcept {
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

      is_annu ? sum_->setText(res_arr[0]) : sum_->setText(res_arr[i]);

      addVbox->addLayout(hboxLayout);
      count_++;
    }
}

void credit::DelRow() noexcept {
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

bool credit::DataIsCorrect() noexcept {
    QString sum_ = ui->creditSum->text();
    QString term_ = ui->creditTerm->text();
    QString percent_ = ui->percent->text();
    if (calc_.IsCorrectInt(term_) && calc_.IsCorrectDec(sum_) && calc_.IsCorrectDec(percent_))
        return true;
    else
        return false;
}

void credit::on_showResult_clicked() noexcept {
  const double sum_ = ui->creditSum->text().toDouble();
  const int term_ = ui->month->isChecked() ? ui->creditTerm->text().toInt() : ui->creditTerm->text().toInt() * 12;
  if (term_ > 600) {
      QMessageBox msg_box_;
      msg_box_.setText("Срок должен быть не больше 50 лет (600 месяцев).");
      msg_box_.exec();
  } else {
      if (DataIsCorrect()) {
        DelRow();
        this->setFixedSize(960, 480);
        ui->monthRes->clear();
        ui->overPay->clear();
        ui->resultSum->clear();
        QVector<QString> result_;
        calc_.set_sum(sum_);
        calc_.set_term(term_);
        calc_.set_percent(ui->percent->text());
        if (ui->annu->isChecked()) {
          result_ = calc_.AnnuCred();
          ui->overPay->setText(result_[1]);
          ui->monthRes->setText(result_[0]);
          ui->resultSum->setText(result_[2]);
          AddRow(term_, result_, true);
        } else {
          result_ = calc_.DifferCred();
          ui->overPay->setText(result_.front());
          ui->resultSum->setText(result_[result_.size() - 2]);
          ui->monthRes->setText(result_[1] + " ... " + result_.back());
          AddRow(term_, result_, false);
        }
      } else {
          QMessageBox msg_box_;
          msg_box_.setText("Вы ввели некорректные данные!");
          msg_box_.exec();
      }
  }
}
