#include "controller/controller.h"

int main() {
  std::cout << std::endl;
  s21::controller calc_;

//   double result_ = calc_.Calculator("(-(sqrt(abs(cos(x)))*cos(200*x)+sqrt(abs(x))-Pi/4*abs(4-x^2)^0.01))=");

//   std::cout << result_ << std::endl;

  calc_.GraphStart("(-(sqrt(abs(cos(x)))*cos(200*x)+sqrt(abs(x))-Pi/4*abs(4-x^2)^0.01))=");
  for (double x = -200; x <= 200.01; x += 0.01) {
    std::cout << calc_.Graph(x) << std::endl;
  }
  calc_.GraphEnd();

  std::cout << std::endl;
  return 0;
}
