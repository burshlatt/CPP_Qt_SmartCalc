#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  secondWindow = new CreditWindow();
  connect(secondWindow, &CreditWindow::firstWindow, this, &MainWindow::show);

  thirdWindow = new DepositWindow();
  connect(thirdWindow, &DepositWindow::firstWindow, this, &MainWindow::show);

  this->setFixedSize(480, 380);

  QScreen *screen = QGuiApplication::primaryScreen();
  QRect screenGeometry = screen->geometry();
  int x = (screenGeometry.width() - 480) / 2;
  int y = (screenGeometry.height() - 380) / 2;
  move(x, y);

  ui->xValue->setPlaceholderText("Значение X");
  ui->xMaxCord->setPlaceholderText("X макс.");
  ui->xMinCord->setPlaceholderText("X мин.");
  ui->yMaxCord->setPlaceholderText("Y макс.");
  ui->yMinCord->setPlaceholderText("Y мин.");
  ui->xStart->setPlaceholderText("X начало");
  ui->xEnd->setPlaceholderText("X конец");

  connect(ui->lnFunc, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->logFunc, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->absFunc, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->cosFunc, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->sinFunc, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->tanFunc, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->acosFunc, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->asinFunc, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->atanFunc, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->sqrtFunc, SIGNAL(clicked()), this, SLOT(func_clicked()));

  connect(ui->xSym, SIGNAL(clicked()), this, SLOT(symbols_clicked()));
  connect(ui->num_0, SIGNAL(clicked()), this, SLOT(symbols_clicked()));
  connect(ui->num_1, SIGNAL(clicked()), this, SLOT(symbols_clicked()));
  connect(ui->num_2, SIGNAL(clicked()), this, SLOT(symbols_clicked()));
  connect(ui->num_3, SIGNAL(clicked()), this, SLOT(symbols_clicked()));
  connect(ui->num_4, SIGNAL(clicked()), this, SLOT(symbols_clicked()));
  connect(ui->num_5, SIGNAL(clicked()), this, SLOT(symbols_clicked()));
  connect(ui->num_6, SIGNAL(clicked()), this, SLOT(symbols_clicked()));
  connect(ui->num_7, SIGNAL(clicked()), this, SLOT(symbols_clicked()));
  connect(ui->num_8, SIGNAL(clicked()), this, SLOT(symbols_clicked()));
  connect(ui->num_9, SIGNAL(clicked()), this, SLOT(symbols_clicked()));
  connect(ui->num_pi, SIGNAL(clicked()), this, SLOT(symbols_clicked()));

  connect(ui->addFunc, SIGNAL(clicked()), this, SLOT(operators_clicked()));
  connect(ui->mulFunc, SIGNAL(clicked()), this, SLOT(operators_clicked()));
  connect(ui->divFunc, SIGNAL(clicked()), this, SLOT(operators_clicked()));
  connect(ui->powFunc, SIGNAL(clicked()), this, SLOT(operators_clicked()));
  connect(ui->modFunc, SIGNAL(clicked()), this, SLOT(operators_clicked()));

  connect(ui->leftBracket, SIGNAL(clicked()), this, SLOT(brackets_clicked()));
  connect(ui->rightBracket, SIGNAL(clicked()), this, SLOT(brackets_clicked()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_credCalc_clicked() {
  secondWindow->show();
  this->close();
}

void MainWindow::on_deposCalc_clicked() {
  thirdWindow->show();
  this->close();
}

void MainWindow::GetInfo() {
  button_ = (QPushButton *)sender();
  str_ = ui->inputOutput->text().toStdString();
  last_symbol_ = str_.back();
  size_ = str_.size();
  if (size_ >= 255) {
    ui->inputOutput->clear();
    ui->inputOutput->setText(ui->inputOutput->text() + "ERROR: Too many elements!");
  }
}

void MainWindow::operators_clicked() {
    GetInfo();
    bool is_operator_ = false;
    if (size_ && last_symbol_ != '(' && last_symbol_ != '.') {
        for (int i = 0; i < 6; i++) {
            if (last_symbol_ == operators[i]) {
                if (last_symbol_ != '-' || str_[str_.size() - 2] != '(') {
                    is_operator_ = true;
                }
            }
        }
        if (is_operator_) {
            if (last_symbol_ == 'd') {
                on_delElem_clicked();
                on_delElem_clicked();
            }
            on_delElem_clicked();
        }
        if (size_ < 255) {
          ui->inputOutput->setText(ui->inputOutput->text() + button->text());
          is_dot_ = false;
        }
    }
}

void MainWindow::symbols_clicked() {
    GetInfo();
    if (size_ < 255) {
        if (last_symbol_ == 'x' || last_symbol_ == ')' || last_symbol_ == 'i') {
            ui->inputOutput->setText(ui->inputOutput->text() + "*");
        }
        if (button->text() == "Pi" && last_symbol_ != '.') {
            if (last_symbol_ >= '0' && last_symbol_ <= '9') {
                ui->inputOutput->setText(ui->inputOutput->text() + "*");
            }
            ui->inputOutput->setText(ui->inputOutput->text() + button->text());
            is_dot_ = 0;
        } else if (button->text() == 'x' && last_symbol_ != '.') {
            if (last_symbol_ >= '0' && last_symbol_ <= '9') {
                ui->inputOutput->setText(ui->inputOutput->text() + "*");
            }
            ui->inputOutput->setText(ui->inputOutput->text() + "x");
            is_dot_ = 0;
        } else if (button->text() >= '0' && button->text() <= '9') {
            ui->inputOutput->setText(ui->inputOutput->text() + button->text());
        }
    }
}

void MainWindow::func_clicked() {
  GetInfo();
  if (size_ < 255 && last_symbol_ != '.') {
    if ((last_symbol_ >= '0' && last_symbol_ <= '9') || last_symbol_ == ')' ||
        last_symbol_ == 'i') {
      ui->inputOutput->setText(ui->inputOutput->text() + "*");
    }
    ui->inputOutput->setText(ui->inputOutput->text() + button->text() + "(");
    is_dot_ = 0;
  }
}

void MainWindow::brackets_clicked() {
  GetInfo();
  l_brackets_ = 0;
  r_brackets_ = 0;
  bool can_do_ = true;
  if (last_symbol_ != '.') {
    for (size_t i = 0; i < size_; i++) {
      if (str_[i] == '(') {
        l_brackets_++;
      }
      if (str_[i] == ')') {
        r_brackets_++;
      }
    }
    if (size_ < 255) {
      if (button->text() == '(') {
        if ((last_symbol_ >= '0' && last_symbol_ <= '9') || last_symbol_ == 'x' ||
            last_symbol_ == ')') {
          ui->inputOutput->setText(ui->inputOutput->text() + "*");
        }
        ui->inputOutput->setText(ui->inputOutput->text() + "(");
        is_dot_ = 0;
      }
      if (button->text() == ')' &&
          r_brackets_ < l_brackets_) {
        for (int i = 0; i < 6; i++) {
          if (last_symbol_ == operators[i]) {
            can_do_ = false;
          }
        }
        if (can_do) {
          ui->inputOutput->setText(ui->inputOutput->text() + ")");
          is_dot_ = 0;
        }
      }
    }
  }
}

void MainWindow::on_subFunc_clicked() {
  GetInfo();
  if (size_ < 255 && last_symbol_ != '.') {
    if (size_ == 0) {
      ui->inputOutput->setText(ui->inputOutput->text() + "(");
    } else {
      for (int i = 0; i < 6; i++) {
        if (last_symbol_ == operators[i]) {
          ui->inputOutput->setText(ui->inputOutput->text() + "(");
          break;
        }
      }
    }
    ui->inputOutput->setText(ui->inputOutput->text() + "-");
    is_dot_ = 0;
  }
}

void MainWindow::on_dotSym_clicked() {
  GetInfo();
  if (size_ < 255 && last_symbol_ != '.' && !is_dot_) {
    if (last_symbol_ < '0' || last_symbol_ > '9') {
      if (last_symbol_ == ')') {
        ui->inputOutput->setText(ui->inputOutput->text() + "*");
      }
      ui->inputOutput->setText(ui->inputOutput->text() + "0");
    }
    ui->inputOutput->setText(ui->inputOutput->text() + ".");
    is_dot_ = 1;
  }
}

void MainWindow::on_delElem_clicked() {
  GetInfo();
  if (last_symbol_ == '.') {
    is_dot_ = 0;
  }
  if (size_ == 0) {
    ui->inputOutput->clear();
  } else {
    QString text = ui->inputOutput->text();
    text.chop(1);
    ui->inputOutput->setText(text);
  }
  GetInfo();
  for (int i = str_.size() - 1;
       str_[i] >= '0' && str_[i] <= '9'; i--) {
    if (str_[i - 1] == '.') {
      is_dot_ = 1;
    }
  }
}

void MainWindow::on_delAll_clicked() {
  is_x_ = false;
  is_dot_ = false;
  ui->inputOutput->clear();
}

void MainWindow::check_fields() {
  if (ui->xValue->text().size() == 0) {
    ui->xValue->setText("0");
  }
  if (ui->xMinCord->text().size() == 0) {
    ui->xMinCord->setText("-5");
  } else if (ui->xMinCord->text().toDouble() < -1000000) {
    ui->xMinCord->setText("-1000000");
  }
  if (ui->xMaxCord->text().size() == 0) {
    ui->xMaxCord->setText("5");
  } else if (ui->xMaxCord->text().toDouble() > 1000000) {
    ui->xMaxCord->setText("1000000");
  }
  if (ui->yMinCord->text().size() == 0) {
    ui->yMinCord->setText("-5");
  } else if (ui->yMinCord->text().toDouble() < -1000000) {
    ui->yMinCord->setText("-1000000");
  }
  if (ui->yMaxCord->text().size() == 0) {
    ui->yMaxCord->setText("5");
  } else if (ui->yMaxCord->text().toDouble() > 1000000) {
    ui->yMaxCord->setText("1000000");
  }
  if (ui->xStart->text().size() == 0) {
    ui->xStart->setText("-200");
  } else if (ui->xStart->text().toDouble() < -1000000) {
    ui->xStart->setText("-1000000");
  }
  if (ui->xEnd->text().size() == 0) {
    ui->xEnd->setText("200");
  } else if (ui->xEnd->text().toDouble() > 1000000) {
    ui->xEnd->setText("1000000");
  }
}

void MainWindow::on_resultFunc_clicked() {
  error_status = 0;
  check_fields();
  int can_do = 1;
  double xValue = ui->xValue->text().toDouble();
  std::string final_string = ui->inputOutput->text().toStdString();
  char *chars_array = &final_string[0];
  double result = polish_notation(chars_array, is_x, xValue, &error_status);
  for (int i = 0; i < 6; i++) {
    if (final_string[final_string.size() - 1] == operators[i]) {
      can_do = 0;
    }
  }
  for (int i = 0; final_string[i] != '\0'; i++) {
    if (final_string[i] == 'x') {
      is_x = 1;
    }
  }
  if (!can_do) {
    ui->inputOutput->setText(ui->inputOutput->text() + "1");
  } else if (error_status) {
    ui->inputOutput->setText(ui->inputOutput->text() + "2");
  }
  if (!error_status && can_do && chars_array[0] != '-') {
    if (is_x) {
      if (!graph_is_open) {
        int xPos = this->geometry().x();
        int yPos = this->geometry().y();
        this->setFixedSize(960, 380);
        ui->showGraph->setText("<");
        setGeometry(xPos, yPos, width() + 480, height());
        graph_is_open = 1;
      }
      print_graph(chars_array);
      is_x = 0;
    } else {
      ui->inputOutput->clear();
      if (fabs(result - (int)result) < 0.00000001) {
        ui->inputOutput->setText(ui->inputOutput->text() +
                                 QString::number(result, 'f', 0));
      } else {
        ui->inputOutput->setText(ui->inputOutput->text() +
                                 QString::number(result, 'f', 7));
      }
    }
  } else if (error_status == 2 && can_do) {
    ui->inputOutput->clear();
    ui->inputOutput->setText(ui->inputOutput->text() +
                             "ERROR: Division by zero!");
  } else {
    ui->inputOutput->clear();
    ui->inputOutput->setText(ui->inputOutput->text() +
                             "ERROR: Incorrect data!");
  }
}

void MainWindow::on_showGraph_clicked() {
  int xPos = this->geometry().x();
  int yPos = this->geometry().y();
  if (!graph_is_open) {
    this->setFixedSize(960, 380);
    ui->showGraph->setText("<");
    setGeometry(xPos, yPos, width() + 480, height());
    graph_is_open = 1;
  } else {
    this->setFixedSize(480, 380);
    ui->showGraph->setText(">");
    setGeometry(xPos, yPos, width() - 480, height());
    graph_is_open = 0;
  }
}

void MainWindow::print_graph(char *chars_array) {
  check_fields();
  ui->functionGraph->clearGraphs();
  int xMin = ui->xMinCord->text().toInt();
  int xMax = ui->xMaxCord->text().toInt();
  int yMin = ui->yMinCord->text().toInt();
  int yMax = ui->yMaxCord->text().toInt();
  ui->functionGraph->xAxis->setRange(xMin, xMax);
  ui->functionGraph->yAxis->setRange(yMin, yMax);
  double h = 0.01;
  double xBegin = ui->xStart->text().toDouble();
  double xEnd = ui->xEnd->text().toDouble() + h;
  double X = xBegin;
  error_status = 0;
  QVector<double> xCord, yCord;
  while (X <= xEnd) {
    double result = polish_notation(chars_array, is_x, X, &error_status);
    xCord.push_back(X);
    yCord.push_back(result);
    X += h;
  }
  ui->functionGraph->addGraph();
  ui->functionGraph->graph(0)->addData(xCord, yCord);
  ui->functionGraph->replot();
}
