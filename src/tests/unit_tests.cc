#include <gtest/gtest.h>
#include "../model/model_calculator.h"

TEST(SmartCalc, simple_operations) {
  s21::ModelCalculator calc_;
  calc_.Notation("((4-9)/(7+9)*3)^6=");
  calc_.Calculations();
  calc_.ClearOutput();
  EXPECT_EQ(calc_.get_res(), 0.67893415689468384);
}

TEST(SmartCalc, cos_rad) {
  s21::ModelCalculator calc_;
  calc_.set_rad(true);
  calc_.Notation("4^cos(2/4)=");
  calc_.Calculations();
  calc_.ClearOutput();
  EXPECT_EQ(calc_.get_res(), 3.3756495226569894);
}

TEST(SmartCalc, cos_deg) {
  s21::ModelCalculator calc_;
  calc_.set_rad(false);
  calc_.Notation("4^cos(2/4)=");
  calc_.Calculations();
  calc_.ClearOutput();
  EXPECT_EQ(calc_.get_res(), 3.9997888622068798);
}

TEST(SmartCalc, sin_rad) {
  s21::ModelCalculator calc_;
  calc_.set_rad(true);
  calc_.Notation("4^sin(2/4)=");
  calc_.Calculations();
  calc_.ClearOutput();
  EXPECT_EQ(calc_.get_res(), 1.9437613200412307);
}

TEST(SmartCalc, sin_deg) {
  s21::ModelCalculator calc_;
  calc_.set_rad(false);
  calc_.Notation("4^sin(2/4)=");
  calc_.Calculations();
  calc_.ClearOutput();
  EXPECT_EQ(calc_.get_res(), 1.012171018249884);
}

TEST(SmartCalc, tan_rad) {
  s21::ModelCalculator calc_;
  calc_.set_rad(true);
  calc_.Notation("4^tan(2/4)=");
  calc_.Calculations();
  calc_.ClearOutput();
  EXPECT_EQ(calc_.get_res(), 2.1325875638524256);
}

TEST(SmartCalc, tan_deg) {
  s21::ModelCalculator calc_;
  calc_.set_rad(false);
  calc_.Notation("4^tan(2/4)=");
  calc_.Calculations();
  calc_.ClearOutput();
  EXPECT_EQ(calc_.get_res(), 1.0121714845116918);
}

TEST(SmartCalc, acos_rad) {
  s21::ModelCalculator calc_;
  calc_.set_rad(true);
  calc_.Notation("4^acos(2/4)=");
  calc_.Calculations();
  calc_.ClearOutput();
  EXPECT_EQ(calc_.get_res(), 4.2704707206911676);
}

TEST(SmartCalc, acos_deg) {
  s21::ModelCalculator calc_;
  calc_.set_rad(false);
  calc_.Notation("4^acos(2/4)=");
  calc_.Calculations();
  calc_.ClearOutput();
  EXPECT_EQ(calc_.get_res(), 8.7188577402320604);
}

TEST(SmartCalc, asin_rad) {
  s21::ModelCalculator calc_;
  calc_.set_rad(true);
  calc_.Notation("4^asin(2/4)=");
  calc_.Calculations();
  calc_.ClearOutput();
  EXPECT_EQ(calc_.get_res(), 2.0665117276926273);
}

TEST(SmartCalc, asin_deg) {
  s21::ModelCalculator calc_;
  calc_.set_rad(false);
  calc_.Notation("4^asin(2/4)=");
  calc_.Calculations();
  calc_.ClearOutput();
  EXPECT_EQ(calc_.get_res(), 1.0121713290898817);
}

TEST(SmartCalc, atan_rad) {
  s21::ModelCalculator calc_;
  calc_.set_rad(true);
  calc_.Notation("4^atan(2/4)=");
  calc_.Calculations();
  calc_.ClearOutput();
  EXPECT_EQ(calc_.get_res(), 1.9017073081110643);
}

TEST(SmartCalc, atan_deg) {
  s21::ModelCalculator calc_;
  calc_.set_rad(false);
  calc_.Notation("4^atan(2/4)=");
  calc_.Calculations();
  calc_.ClearOutput();
  EXPECT_EQ(calc_.get_res(), 1.0121708628458983);
}

TEST(SmartCalc, abs_test) {
  s21::ModelCalculator calc_;
  calc_.Notation("4^abs(-3)=");
  calc_.Calculations();
  calc_.ClearOutput();
  EXPECT_EQ(calc_.get_res(), 64);
}

TEST(SmartCalc, sqrt_test) {
  s21::ModelCalculator calc_;
  calc_.Notation("4^sqrt(9)=");
  calc_.Calculations();
  calc_.ClearOutput();
  EXPECT_EQ(calc_.get_res(), 64);
}

TEST(SmartCalc, log_test) {
  s21::ModelCalculator calc_;
  calc_.Notation("4^log(9)=");
  calc_.Calculations();
  calc_.ClearOutput();
  EXPECT_EQ(calc_.get_res(), 3.7541466784489006);
}

TEST(SmartCalc, ln_test) {
  s21::ModelCalculator calc_;
  calc_.Notation("4^ln(9)=");
  calc_.Calculations();
  calc_.ClearOutput();
  EXPECT_EQ(calc_.get_res(), 21.031052619074607);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
