#include "scoreboard.h"

#include <iostream>

namespace game_data {

std::multiset<ScoreEntry, std::greater<>> Scoreboard::saved_scores_;

Scoreboard::Scoreboard() : handler_(SCORES_FILE_PATH) {
  auto scores = handler_.GetSavedScores();
  for (const auto &score : scores) {
    saved_scores_.emplace(score);
  }
}

void Scoreboard::SaveScore(const player::Player &player) {
  if (!IsHighScore(player.GetScore())) {
    return;
  }

  std::cout << "Congratulations, " << player.GetName()
            << "! You made it to the scoreboard!" << std::endl;

  if (saved_scores_.size() >= kScoreLimit &&
      player.GetScore() > saved_scores_.begin()->score) {
    saved_scores_.erase(saved_scores_.begin());
  }

  AddScore(player.GetScore(), player.GetName(), player.GetDifficulty());
  handler_.UpdateScoreboard(saved_scores_);
}

// TODO: FORMAT SCORES
void Scoreboard::PrintScores() const {
  std::cout << "High Scores:" << std::endl;
  std::string header = handler_.HeaderToString("\t");
  std::cout << header << std::endl;

  if (saved_scores_.empty()) {
    std::cout << "No scores found." << std::endl;
    return;
  }

  for (const auto &entry : saved_scores_) {
    std::cout << entry.score << "\t" << entry.name << "\t" << entry.difficulty
              << std::endl;
  }
}

bool Scoreboard::IsHighScore(const int &score) const {
  return saved_scores_.size() < kScoreLimit ||
         score > saved_scores_.begin()->score;
}

void Scoreboard::AddScore(const int &score, const std::string &name,
                          const int &difficulty) {
  saved_scores_.emplace(score, name, difficulty);
}

} // namespace game_data
