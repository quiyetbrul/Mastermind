#include "csv_handler.h"

#include <fstream>
#include <iostream>
#include <sstream>

std::vector<std::pair<std::string, int>> CSVHandler::saved_scores_;

// TODO: need to be singleton
CSVHandler::CSVHandler(const std::string &file_name) : file_name_(file_name) {
  std::ifstream file(file_name_);
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      std::istringstream ss(line);
      std::string name;
      std::string score_str;
      if (std::getline(ss, name, ',') && std::getline(ss, score_str)) {
        int score = std::stoi(score_str);
        AddScore(name, score);
      }
    }
    file.close();
  } else {
    std::cerr << "Failed to open file: " << file_name_ << std::endl;
    std::cerr << "Error: " << strerror(errno)
              << std::endl; // Print the specific error
    std::ofstream file(file_name_);
    if (!file.is_open()) {
      std::cerr << "Failed to create file: " << file_name_ << std::endl;
      std::cerr << "Error: " << strerror(errno)
                << std::endl; // Print the specific error
    } else {
      file.close();
    }
  }
}

void CSVHandler::SetFileName(const std::string &file_name) {
  file_name_ = file_name;
}

void CSVHandler::SaveScore(const player::Player &player) {
  if (saved_scores_.size() > kScoreLimit &&
      player.GetScore() > saved_scores_.back().second) {
    saved_scores_.pop_back();
  }
  AddScore(player.GetName(), player.GetScore());
  UpdateScoreboard();
}

std::vector<std::pair<std::string, int>> CSVHandler::GetScores() const {
  return saved_scores_;
}

void CSVHandler::PrintScores() const {
  for (const auto &entry : saved_scores_) {
    std::cout << entry.first << " " << entry.second << std::endl;
  }
}

bool CSVHandler::IsHighScore(const int &score) const {
  return saved_scores_.size() < kScoreLimit ||
         score > saved_scores_.back().second;
}

void CSVHandler::UpdateScoreboard() {
  std::ofstream file(file_name_);
  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << file_name_ << std::endl;
    return;
  }

  std::cout << "Updating scoreboard in file: " << file_name_ << std::endl;
  for (const auto &entry : saved_scores_) {
    std::cout << "Writing entry: " << entry.first << ", " << entry.second
              << std::endl;
    file << entry.first << "," << entry.second << std::endl;
  }
  file.close();
  std::cout << "Scoreboard updated successfully." << std::endl;
}

void CSVHandler::AddScore(const std::string &name, const int &score) {
  saved_scores_.emplace_back(name, score);
  std::sort(saved_scores_.begin(), saved_scores_.end(),
            [](const auto &a, const auto &b) { return a.second > b.second; });
}
