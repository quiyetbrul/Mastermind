#include "util/util.h"

#include <string>

#include <gtest/gtest.h>
#include <ncurses.h>

const std::string kUserInput = "sim usr input";

// Mock function for wgetnstr
int wgetnstr_mock(WINDOW *window, char *str, int n) {
  strncpy(str, kUserInput.c_str(), n);
  str[n - 1] = '\0';
  return OK;
}

// Replace wgetnstr with mock function
#define wgetnstr wgetnstr_mock

#include "input_validation.cpp"

class InputValidationTest : public ::testing::Test {
protected:
  WINDOW *window_;

  void SetUp() override {
    initscr();
    window_ = newwin(10, 40, 0, 0);
  }

  void TearDown() override {
    delwin(window_);
    endwin();
  }
};

// Test case for valid input
TEST_F(InputValidationTest, ValidInput) {
  std::string result = InputString(window_, 1, "Enter your name: ");
  EXPECT_EQ(result, kUserInput);
}

// Test case for empty input
TEST_F(InputValidationTest, EmptyInput) {
  std::string expected_input = "";
  std::string result = InputString(window_, 1, "Enter your name: ");
  EXPECT_NE(result, expected_input);
}
