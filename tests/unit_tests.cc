#include <gtest/gtest.h>
#include <cmath>

#include "../src/model/calc/model_calc.hpp"

TEST(SmartCalc, pow_test) {
  CalcModel calc;
  EXPECT_EQ(*calc.Calculate("((4-9)/(7+9)*3)^6"), pow(((4.0 - 9.0) / (7.0 + 9.0) * 3.0), 6.0));
}

TEST(SmartCalc, cos_rad) {
  CalcModel calc;
  EXPECT_EQ(*calc.Calculate("4^cos(2/4)"), pow(4.0, cos(2.0 / 4.0)));
}

TEST(SmartCalc, sin_rad) {
  CalcModel calc;
  EXPECT_EQ(*calc.Calculate("4^sin(2/4)"), pow(4.0, sin(2.0 / 4.0)));
}

TEST(SmartCalc, tan_rad) {
  CalcModel calc;
  EXPECT_EQ(*calc.Calculate("4^tan(2/4)"), pow(4.0, tan(2.0 / 4.0)));
}

TEST(SmartCalc, acos_rad) {
  CalcModel calc;
  EXPECT_EQ(*calc.Calculate("4^acos(2/4)"), std::pow(4.0, acos(2.0 / 4.0)));
}

TEST(SmartCalc, asin_rad) {
  CalcModel calc;
  EXPECT_EQ(*calc.Calculate("4^asin(2/4)"), std::pow(4.0, asin(2.0 / 4.0)));
}

TEST(SmartCalc, atan_rad) {
  CalcModel calc;
  EXPECT_EQ(*calc.Calculate("4^atan(2/4)"), std::pow(4.0, atan(2.0 / 4.0)));
}

TEST(SmartCalc, abs_test) {
  CalcModel calc;
  EXPECT_EQ(*calc.Calculate("4^abs(-3)"), std::pow(4.0, abs(-3.0)));
}

TEST(SmartCalc, sqrt_test) {
  CalcModel calc;
  EXPECT_EQ(*calc.Calculate("4^sqrt(9)"), std::pow(4.0, sqrt(9.0)));
}

TEST(SmartCalc, log_test) {
  CalcModel calc;
  EXPECT_EQ(*calc.Calculate("4^log(9)"), std::pow(4.0, log10(9.0)));
}

TEST(SmartCalc, ln_test) {
  CalcModel calc;
  EXPECT_EQ(*calc.Calculate("4^ln(9)"), std::pow(4.0, log(9.0)));
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

