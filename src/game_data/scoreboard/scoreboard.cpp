#include "scoreboard.h"

#include <iostream>

namespace game_data {

std::vector<std::pair<std::string, int>> Scoreboard::saved_scores_;

Scoreboard::Scoreboard() : handler_(SCORES_FILE_PATH) {
  saved_scores_ = handler_.GetSavedScores();
}

void Scoreboard::SaveScore(const player::Player &player) {
  if (!IsHighScore(player.GetScore())) {
    return;
  }
  std::cout << "Congratulations, " << player.GetName() <<"! You made it to the scoreboard!" << std::endl;
  if (saved_scores_.size() > kScoreLimit &&
      player.GetScore() > saved_scores_.back().second) {
    saved_scores_.pop_back();
  }
  AddScore(player.GetName(), player.GetScore());
  handler_.UpdateScoreboard(saved_scores_);
}

// TODO: FORMAT SCORES
void Scoreboard::PrintScores() const {
  if (saved_scores_.empty()) {
    std::cout << "No scores found." << std::endl;
    return;
  }
  for (const auto &entry : saved_scores_) {
    std::cout << entry.first << "    " << entry.second << std::endl;
  }
}

bool Scoreboard::IsHighScore(const int &score) const {
  return saved_scores_.size() < kScoreLimit ||
         score > saved_scores_.back().second;
}

void Scoreboard::AddScore(const std::string &name, const int &score) {
  saved_scores_.emplace_back(name, score);
  std::sort(
      saved_scores_.begin(), saved_scores_.end(),
      [](const auto &lhs, const auto &rhs) { return lhs.second > rhs.second; });
}

} // namespace game_data
