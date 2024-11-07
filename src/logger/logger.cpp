/**
 * @file logger.h
 * @brief Implementation of a logger class.
 */

#include "logger.h"

#include <chrono>
#include <cstring>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <sstream>

void Logger::SetOutputFile(const std::string &file_name) {
  output_file_name_ = file_name;
  Init();
  output_file_.open(output_file_name_, std::ios::out | std::ios::app);
  if (!output_file_.is_open()) {
    std::cerr << "Failed to open log file: " << file_name << std::endl;
  }
}

void Logger::Init() {
  std::ifstream file(output_file_name_);
  if (!file.is_open()) {
    std::cerr << "Logger: Failed to open file: " << output_file_name_
              << std::endl;
    std::cerr << "Logger: " << strerror(errno) << std::endl;

    // Create the necessary directories and file
    std::filesystem::create_directories(
        std::filesystem::path(output_file_name_).parent_path());
    std::cerr << "Logger: Creating leaderboard file: " << output_file_name_
              << std::endl;
    std::ofstream create_file(output_file_name_);
    if (!create_file.is_open()) {
      std::cerr << "Logger: Failed to create file: " << output_file_name_
                << std::endl;
      std::cerr << "Error: " << strerror(errno) << std::endl;
    } else {
      create_file.close();
    }
  }
}

void Logger::Log(const std::string &message) {
  if (output_file_.is_open() && output_file_.good()) {
    output_file_ << GetCurrentTime() << "\t" << message << std::endl;
    output_file_.flush(); // Ensure the data is written to the file
  } else {
    std::cerr << "Log: Failed to write to file: " << output_file_.rdstate()
              << std::endl;
  }
}

void Logger::CloseOutputFile() {
  if (output_file_.is_open()) {
    output_file_.close();
  }
}

std::string Logger::GetCurrentTime() const {
  auto now = std::chrono::system_clock::now();
  auto now_time_t = std::chrono::system_clock::to_time_t(now);
  auto now_tm = *std::localtime(&now_time_t);

  std::ostringstream oss;
  oss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
  return oss.str();
}
