#include <gtest/gtest.h>

#define CALCULATOR_H

#include "../model/model.h"

TEST(SmartCalc, operations_1) {
  s21::model calc_;
  calc_.Notation("4+9+7+9");
  calc_.Calculations();
  calc_.ClearOutput();
  double res_ = calc_.get_res();
  EXPECT_EQ(res_, 29);
}

TEST(SmartCalc, operations_2) {
  s21::model calc_;
  calc_.Notation("4+9/2*67787");
  calc_.Calculations();
  calc_.ClearOutput();
  double res_ = calc_.get_res();
  EXPECT_EQ(res_, 305045.5);
}

TEST(SmartCalc, func_1) {
  s21::model calc_;
  calc_.Notation("(4^acos(2/4))");
  calc_.Calculations();
  calc_.ClearOutput();
  double res_ = calc_.get_res();
  EXPECT_EQ(res_, 4.27047);
}

TEST(SmartCalc, func_2) {
  s21::model calc_;
  calc_.Notation("(tan(2*2))");
  calc_.Calculations();
  calc_.ClearOutput();
  double res_ = calc_.get_res();
  EXPECT_EQ(res_, 1.1578213);
}

TEST(SmartCalc, func_3) {
  s21::model calc_;
  calc_.Notation("(4^acos(2/4)/tan(2*2))");
  calc_.Calculations();
  calc_.ClearOutput();
  double res_ = calc_.get_res();
  EXPECT_EQ(res_, 3.6883678);
}

TEST(SmartCalc, func_4) {
  s21::model calc_;
  calc_.Notation("(4^acos(2/4)/tan(2*2)/5^acos(2/4))");
  calc_.Calculations();
  calc_.ClearOutput();
  double res_ = calc_.get_res();
  EXPECT_EQ(res_, 0.68371409);
}

TEST(SmartCalc, func_5) {
  s21::model calc_;
  calc_.Notation("(4^acos(2/4)/tan(2*2)/5^acos(2/4)/tan(tan(tan(2*2))))");
  calc_.Calculations();
  calc_.ClearOutput();
  double res_ = calc_.get_res();
  EXPECT_EQ(res_, -0.58934796);
}

TEST(SmartCalc, func_6) {
  s21::model calc_;
  calc_.Notation("3^cos(0.5)/5");
  calc_.Calculations();
  calc_.ClearOutput();
  double res_ = calc_.get_res();
  EXPECT_EQ(res_, 0.52449733);
}

TEST(SmartCalc, func_7) {
  s21::model calc_;
  calc_.Notation("3^cos(0.5)/sqrt(25)");
  calc_.Calculations();
  calc_.ClearOutput();
  double res_ = calc_.get_res();
  EXPECT_EQ(res_, 0.52449733);
}

TEST(SmartCalc, func_8) {
  s21::model calc_;
  calc_.Notation("log(10)");
  calc_.Calculations();
  calc_.ClearOutput();
  double res_ = calc_.get_res();
  EXPECT_EQ(res_, 1);
}

TEST(SmartCalc, func_9) {
  s21::model calc_;
  calc_.Notation("1+2*(3^sin(0.4))^3*2+1");
  calc_.Calculations();
  calc_.ClearOutput();
  double res_ = calc_.get_res();
  EXPECT_EQ(res_, 16.436413);
}

TEST(SmartCalc, func_10) {
  s21::model calc_;
  calc_.Notation("ln(10)");
  calc_.Calculations();
  calc_.ClearOutput();
  double res_ = calc_.get_res();
  EXPECT_EQ(res_, 2.3025851);
}

TEST(SmartCalc, func_11) {
  s21::model calc_;
  calc_.Notation("1+2*3^sin(0.4)^3*2+1");
  calc_.Calculations();
  calc_.ClearOutput();
  double res_ = calc_.get_res();
  EXPECT_EQ(res_, 6.291162);
}

TEST(SmartCalc, func_12) {
  s21::model calc_;
  calc_.Notation("1+2*3^sin(0.4)^56*2+1");
  calc_.Calculations();
  calc_.ClearOutput();
  double res_ = calc_.get_res();
  EXPECT_EQ(res_, 6);
}

TEST(SmartCalc, func_13) {
  s21::model calc_;
  calc_.Notation("acos(-0.5)+asin(-0.5)+atan(0.1)*cos(30)*sin(20)*tan(45)");
  calc_.Calculations();
  calc_.ClearOutput();
  double res_ = calc_.get_res();
  EXPECT_EQ(res_, 1.5935309);
}

TEST(SmartCalc, func_14) {
  s21::model calc_;
  calc_.Notation("(-5)^(-4)");
  calc_.Calculations();
  calc_.ClearOutput();
  double res_ = calc_.get_res();
  EXPECT_EQ(res_, 0.0016);
}

TEST(SmartCalc, func_15) {
  s21::model calc_;
  calc_.Notation("-4+5");
  calc_.Calculations();
  calc_.ClearOutput();
  double res_ = calc_.get_res();
  EXPECT_EQ(res_, 1);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
