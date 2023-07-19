#include "view_calculator.h"
#include "ui_view_calculator.h"

ViewCalculator::ViewCalculator(QWidget *parent) : QMainWindow(parent), ui_(new Ui::ViewCalculator) {
  ui_->setupUi(this);

  credit_ = new ViewCredit();
  connect(credit_, &ViewCredit::firstWindow, this, &ViewCalculator::show);

  deposit_ = new ViewDeposit();
  connect(deposit_, &ViewDeposit::firstWindow, this, &ViewCalculator::show);

  this->setFixedSize(480, 380);

  QScreen *screen = QGuiApplication::primaryScreen();
  QRect screenGeometry = screen->geometry();
  const int x = (screenGeometry.width() - 480) / 2;
  const int y = (screenGeometry.height() - 380) / 2;
  move(x, y);

  QVector<QPushButton *> functions_ = {ui_->ln, ui_->log, ui_->abs, ui_->cos, ui_->sin, ui_->tan, ui_->acos, ui_->asin, ui_->atan, ui_->sqrt};
  QVector<QPushButton *> symbols_ = {ui_->num_x, ui_->num_0, ui_->num_1, ui_->num_2, ui_->num_3, ui_->num_4, ui_->num_5, ui_->num_6, ui_->num_7, ui_->num_8, ui_->num_9, ui_->num_pi};
  QVector<QPushButton *> operators_ = {ui_->add, ui_->mul, ui_->div, ui_->pow, ui_->mod};
  QVector<QPushButton *> brackets_ = {ui_->leftBracket, ui_->rightBracket};

  for (auto function_ : functions_)
      connect(function_, SIGNAL(clicked()), this, SLOT(FuncClicked()));
  for (auto symbol_ : symbols_)
      connect(symbol_, SIGNAL(clicked()), this, SLOT(SymbolsClicked()));
  for (auto operator_ : operators_)
      connect(operator_, SIGNAL(clicked()), this, SLOT(OperatorsClicked()));
  for (auto bracket_ : brackets_)
      connect(bracket_, SIGNAL(clicked()), this, SLOT(BracketsClicked()));

  connect(ui_->rad, SIGNAL(clicked()), this, SLOT(RadClicked()));
  connect(ui_->deg, SIGNAL(clicked()), this, SLOT(DegClicked()));
  connect(ui_->dot, SIGNAL(clicked()), this, SLOT(DotClicked()));
  connect(ui_->sub, SIGNAL(clicked()), this, SLOT(SubClicked()));
  connect(ui_->result, SIGNAL(clicked()), this, SLOT(ResultClicked()));
  connect(ui_->delAll, SIGNAL(clicked()), this, SLOT(DelAllClicked()));
  connect(ui_->delElem, SIGNAL(clicked()), this, SLOT(DelElemClicked()));
  connect(ui_->credCalc, SIGNAL(clicked()), this, SLOT(CredCalcClicked()));
  connect(ui_->deposCalc, SIGNAL(clicked()), this, SLOT(DeposCalcClicked()));
  connect(ui_->showGraph, SIGNAL(clicked()), this, SLOT(ShowGraphClicked()));
}

ViewCalculator::~ViewCalculator() { delete ui_; }

void ViewCalculator::CredCalcClicked() noexcept {
  credit_->show();
  this->close();
}

void ViewCalculator::DeposCalcClicked() noexcept {
  deposit_->show();
  this->close();
}

void ViewCalculator::GetInfo() noexcept {
  button_ = (QPushButton *)sender();
  str_ = ui_->input->text().toStdString();
  size_ = str_.size();
  if (size_ >= 255) {
    ui_->input->clear();
    ui_->output->clear();
    ui_->output->setText("ERROR: Too many elements!");
  }
}

void ViewCalculator::OperatorsClicked() noexcept {
  GetInfo();
  if (valid_.IsCorrectOperator(str_)) {
    if (valid_.IsOperator(str_))
      DelElemClicked();
    ui_->input->setText(ui_->input->text() + button_->text());
    is_dot_ = false;
  }
}

void ViewCalculator::SymbolsClicked() noexcept {
  GetInfo();
  QString format_str_ = valid_.FormatSymbols(str_.back(), button_, is_dot_);
  ui_->input->setText(ui_->input->text() + format_str_);
}

void ViewCalculator::FuncClicked() noexcept {
  GetInfo();
  QString format_str_ = valid_.FormatFunc(str_, button_, is_dot_);
  ui_->input->setText(ui_->input->text() + format_str_);
}

void ViewCalculator::BracketsClicked() noexcept {
  GetInfo();
  QString format_str_ = valid_.FormatBrackets(str_, button_, is_dot_);
  ui_->input->setText(ui_->input->text() + format_str_);
}

void ViewCalculator::SubClicked() noexcept {
  GetInfo();
  if (size_ < 255 && str_.back() != '.') {
    if (size_ == 0) {
      ui_->input->setText(ui_->input->text() + "(");
    } else {
      for (size_t i = 0; i < operators_skip_.size(); i++) {
        if (str_.back() == operators_skip_[i] && str_.back() != '(') {
          ui_->input->setText(ui_->input->text() + "(");
          break;
        }
      }
    }
    ui_->input->setText(ui_->input->text() + "-");
    is_dot_ = false;
  }
}

void ViewCalculator::DotClicked() noexcept {
  GetInfo();
  for (int i = str_.size() - 1; str_[i] >= '0' && str_[i] <= '9'; i--) {
    if (str_[i - 1] == '.') {
      is_dot_ = true;
    }
  }
  if (size_ < 255 && str_.back() != '.' && !is_dot_) {
    if (str_.back() < '0' || str_.back() > '9') {
      if (str_.back() == ')' || str_.back() == 'i' || str_.back() == 'x') {
        ui_->input->setText(ui_->input->text() + "*");
      }
      ui_->input->setText(ui_->input->text() + "0");
    }
    ui_->input->setText(ui_->input->text() + ".");
    is_dot_ = true;
  }
}

void ViewCalculator::DelElemClicked() noexcept {
  GetInfo();
  if (str_.back() == '.') is_dot_ = false;
  if (size_ != 0) {
    const char m_five = str_[str_.size() - 5];
    const char m_four = str_[str_.size() - 4];
    const char m_three = str_[str_.size() - 3];
    const char m_two = str_[str_.size() - 2];
    QString text = ui_->input->text();
    if (str_.back() == '(' && (m_five == 'a' || m_five == 's'))
      text.chop(5);
    else if (str_.back() == '(' && m_five != 'a' &&
             (m_four == 'c' || m_four == 's' || m_four == 't' ||
              m_four == 'a' || m_four == 'l'))
      text.chop(4);
    else if ((str_.back() == '(' && m_three == 'l') ||
             (str_.back() == 'd' && m_three == 'm'))
      text.chop(3);
    else if (str_.back() == 'i' && m_two == 'P')
      text.chop(2);
    else
      text.chop(1);
    ui_->input->setText(text);
  }
}

void ViewCalculator::DelAllClicked() noexcept {
  is_dot_ = false;
  ui_->input->clear();
  ui_->output->clear();
}

bool ViewCalculator::IsCorrectGraph() noexcept {
  bool field_1_ = valid_.IsCorrectDec(ui_->xMinCord->text());
  bool field_2_ = valid_.IsCorrectDec(ui_->xMaxCord->text());
  bool field_3_ = valid_.IsCorrectDec(ui_->yMinCord->text());
  bool field_4_ = valid_.IsCorrectDec(ui_->yMaxCord->text());
  bool field_5_ = valid_.IsCorrectDec(ui_->xStart->text());
  bool field_6_ = valid_.IsCorrectDec(ui_->xEnd->text());
  if (field_1_ && field_2_ && field_3_ && field_4_ && field_5_ && field_6_)
    return true;
  return false;
}

void ViewCalculator::ResultClicked() noexcept {
  ui_->output->clear();
  str_ = ui_->input->text().toStdString();
  if (valid_.IsCorrect(str_) && str_.size()) {
    if (!valid_.IsGraph(str_)) {
      QString result_ = calc_.Calculator(str_ + "=");
      if (!calc_.get_error()) {
        ui_->output->clear();
        ui_->output->setText(result_);
      } else {
        ui_->output->setText("ERROR: Incorrect data!");
      }
    } else {
      if (!graph_open_) {
        const int xPos = this->geometry().x();
        const int yPos = this->geometry().y();
        this->setFixedSize(960, 380);
        ui_->showGraph->setText("<");
        setGeometry(xPos, yPos, width() + 480, height());
        graph_open_ = true;
      }
      PrintGraph();
    }
  } else if (!valid_.IsCorrect(str_) && str_.size()) {
    ui_->output->setText("ERROR: Incorrect data!");
  }
}

void ViewCalculator::ShowGraphClicked() noexcept {
  const int xPos = this->geometry().x();
  const int yPos = this->geometry().y();
  if (!graph_open_) {
    this->setFixedSize(960, 380);
    ui_->showGraph->setText("<");
    setGeometry(xPos, yPos, width() + 480, height());
    graph_open_ = true;
  } else {
    this->setFixedSize(480, 380);
    ui_->showGraph->setText(">");
    setGeometry(xPos, yPos, width() - 480, height());
    graph_open_ = false;
  }
}

void ViewCalculator::PrintGraph() noexcept {
  if (!IsCorrectGraph()) {
      QMessageBox msg_box_;
      msg_box_.setText("Значения полей графика должны быть от -1000000 до 1000000");
      msg_box_.exec();
  } else {
      ui_->output->setText("GRAPH");
      ui_->Graph->clearGraphs();
      ui_->Graph->xAxis->setRange(ui_->xMinCord->text().toDouble(), ui_->xMaxCord->text().toDouble());
      ui_->Graph->yAxis->setRange(ui_->yMinCord->text().toDouble(), ui_->yMaxCord->text().toDouble());
      QVector<double> xCord, yCord;
      double X = ui_->xStart->text().toDouble();
      const double xEnd = ui_->xEnd->text().toDouble() + 0.1;
      calc_.GraphStart(str_ + "=");
      while (X <= xEnd) {
        xCord.push_back(X);
        yCord.push_back(calc_.Graph(X));
        X += 0.1;
      }
      calc_.GraphEnd();
      ui_->Graph->addGraph();
      ui_->Graph->graph(0)->addData(xCord, yCord);
      ui_->Graph->replot();
  }
}

void ViewCalculator::RadClicked() noexcept {
  ui_->rad->setStyleSheet(
      "background-color: rgb(255, 160, 122); color: black; border: 1px solid "
      "gray;");
  ui_->deg->setStyleSheet(
      "background-color: rgb(255, 219, 139); color: black; border: 1px solid "
      "gray;");
  calc_.set_rad(true);
  ResultClicked();
}

void ViewCalculator::DegClicked() noexcept {
  ui_->deg->setStyleSheet(
      "background-color: rgb(255, 160, 122); color: black; border: 1px solid "
      "gray;");
  ui_->rad->setStyleSheet(
      "background-color: rgb(255, 219, 139); color: black; border: 1px solid "
      "gray;");
  calc_.set_rad(false);
  ResultClicked();
}
