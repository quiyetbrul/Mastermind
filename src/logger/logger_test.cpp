#include "logger/logger.h"

#include <filesystem>
#include <fstream>
#include <string>

#include <gtest/gtest.h>

class LoggerTest : public ::testing::Test {
protected:
  void SetUp() override {
    // Prepare the log file
    test_log_file_ = LOGGER_TEST_FILE_PATH;
    Logger::GetInstance().SetOutputFile(test_log_file_);
  }

  void TearDown() override {
    // Clean up the test log file
    Logger::GetInstance().CloseOutputFile();
    std::filesystem::remove(test_log_file_);
  }

  std::string test_log_file_;
};

TEST_F(LoggerTest, LogMessage) {
  Logger &logger = Logger::GetInstance();
  logger.Log("Test message");

  // Verify the log file contains the message
  std::ifstream log_file(test_log_file_);
  ASSERT_TRUE(log_file.is_open());

  std::string line;
  bool found = false;
  while (std::getline(log_file, line)) {
    if (line.find("Test message") != std::string::npos) {
      found = true;
      break;
    }
  }

  EXPECT_TRUE(found);
}

TEST_F(LoggerTest, FileInitialization) {
  // Check if the log file is created
  EXPECT_TRUE(std::filesystem::exists(test_log_file_));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
