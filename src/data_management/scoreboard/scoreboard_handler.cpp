#include "scoreboard_handler.h"

#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

namespace data_management {
void ScoreboardHandler::Init() {
  if (file_name_.empty()) {
    std::cerr << "Initialize: file_name_ is empty" << std::endl;
    return;
  }

  // Define the header
  this->header_ = {"score", "name", "time", "difficulty"};

  std::ifstream file(file_name_);
  if (!file.is_open()) {
    std::cerr << "GetSavedScores: Failed to open file: " << file_name_
              << std::endl;
    std::cerr << "Error: " << strerror(errno) << std::endl;

    // Create the necessary directories and file
    std::filesystem::create_directories(
        std::filesystem::path(file_name_).parent_path());
    std::cerr << "GetSavedScores: Creating leaderboard file: " << file_name_
              << std::endl;
    std::ofstream create_file(file_name_);
    if (!create_file.is_open()) {
      std::cerr << "GetSavedScores: Failed to create file: " << file_name_
                << std::endl;
      std::cerr << "Error: " << strerror(errno) << std::endl;
    } else {
      create_file.close();
    }
  } else {
    file.close();
  }
}

// TODO: can be tested
std::multiset<ScoreEntry, std::greater<>> ScoreboardHandler::GetSavedScores() {
  std::multiset<ScoreEntry, std::greater<>> saved_scores;
  if (file_name_.empty()) {
    std::cerr << "GetSavedScores: file_name_ is empty" << std::endl;
    return saved_scores;
  }

  std::ifstream file(file_name_);
  if (!file.is_open()) {
    std::cerr << "GetSavedScores: Failed to open file: " << file_name_
              << std::endl;
    std::cerr << "Error: " << strerror(errno) << std::endl;
    return saved_scores;
  }

  std::string line;
  std::getline(file, line); // Skip the header
  while (std::getline(file, line)) {
    std::istringstream ss(line);
    std::string score_str, name, time_str, difficulty_str;
    if (std::getline(ss, score_str, ',') && std::getline(ss, name, ',') &&
        std::getline(ss, time_str, ',') && std::getline(ss, difficulty_str)) {
      int score = std::stoi(score_str);
      double time = std::stod(time_str);
      int difficulty = std::stoi(difficulty_str);
      saved_scores.emplace(ScoreEntry{score, name, time, difficulty});
    }
  }
  file.close();
  return saved_scores;
}

// TODO: can be tested
void ScoreboardHandler::UpdateScoreboard(
    const std::multiset<ScoreEntry, std::greater<>> &saved_scores) {
  std::ofstream file(file_name_);
  if (!file.is_open()) {
    std::cerr << "UpdateScoreboard: Failed to open file: " << file_name_
              << std::endl;
    return;
  }

  file << HeaderToString(",") << std::endl;
  for (const auto &entry : saved_scores) {
    file << std::fixed << std::setprecision(3) << entry.score << "," << entry.name
         << "," << entry.elapsed_time << "," << entry.difficulty << std::endl;
  }
  file.close();
}

std::string ScoreboardHandler::HeaderToString(const std::string &delim) const {
  std::string header_str;
  for (int i = 0; i < this->header_.size(); i++) {
    header_str += header_[i];
    if (i != header_.size() - 1) {
      header_str += delim;
    }
  }
  return header_str;
}
} // namespace data_management
