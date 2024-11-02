#include "scoreboard_handler.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

std::multiset<std::pair<int, std::string>, std::greater<>>
ScoreboardHandler::GetSavedScores() const {
  std::multiset<std::pair<int, std::string>, std::greater<>> saved_scores;
  std::ifstream file(file_name_);
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      std::istringstream ss(line);
      std::string name;
      std::string score_str;
      if (std::getline(ss, score_str, ',') && std::getline(ss, name)) {
        int score = std::stoi(score_str);
        saved_scores.emplace(score, name);
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
    std::cerr << "GetSavedScores: Creating leaderboard file: " << file_name_
              << std::endl;

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

  return saved_scores;
}

void ScoreboardHandler::UpdateScoreboard(
    const std::multiset<std::pair<int, std::string>, std::greater<>>
        &saved_scores) {
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
