#include "logger.h"

#include <fstream>
#include <iostream>

// void Logger::SetOutputFile(const std::string &file_name) {
//   output_file_.open(file_name, std::ios::app);
// }

// void Logger::Log(const std::string &message) {
//   if (output_file_.is_open()) {
//     output_file_ << message << std::endl;
//   } else {
//     std::cerr << "Log: Failed to open file: " << output_file_.rdstate()
//               << std::endl;
//   }
// }
