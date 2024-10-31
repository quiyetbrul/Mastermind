#include "scoreboard_handler.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

// TODO: need a func that looks at the file when it first starts and creates it
// if it doesn't exist
std::vector<std::pair<std::string, int>>
ScoreboardHandler::GetSavedScores() const {
  std::vector<std::pair<std::string, int>> saved_scores;
  std::ifstream file(file_name_);
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      std::istringstream ss(line);
      std::string name;
      std::string score_str;
      if (std::getline(ss, name, ',') && std::getline(ss, score_str)) {
        int score = std::stoi(score_str);
        saved_scores.emplace_back(name, score);
      }
    }
    file.close();
  } else {
    // TODO: cerr should be logged to a file instead of printed to the console
    std::cerr << "GetSavedScores: Failed to open file: " << file_name_
              << std::endl;
    std::cerr << "Error: " << strerror(errno)
              << std::endl; // Print the specific error

    // Create the necessary directories
    std::filesystem::create_directories(
        std::filesystem::path(file_name_).parent_path());

    // Attempt to create the file
    std::ofstream create_file(file_name_);
    if (!create_file.is_open()) {
      std::cerr << "GetSavedScores: Failed to create file: " << file_name_
                << std::endl;
      std::cerr << "Error: " << strerror(errno)
                << std::endl; // Print the specific error
    } else {
      create_file.close();
    }
  }

  if (saved_scores.empty()) {
    std::cout << "No scores found." << std::endl;
  }

  return saved_scores;
}

void ScoreboardHandler::UpdateScoreboard(
    const std::vector<std::pair<std::string, int>> &saved_scores) {
  std::ofstream file(file_name_);
  if (!file.is_open()) {
    std::cerr << "UpdateScoreboard: Failed to open file: " << file_name_
              << std::endl;
    return;
  }

  for (const auto &entry : saved_scores) {
    file << entry.first << "," << entry.second << std::endl;
  }
  file.close();
}
