#include "view/view_calculator.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication apl_(argc, argv);
  ViewCalculator calc_;
  calc_.show();
  return apl_.exec();
}
