/**
 * @file player.cpp
 * @brief Implementation of the Player class.
 */

#include "player.h"

#include <algorithm>
#include <cmath>
#include <string>

#include "player/util/util.h"

namespace player {
Player::Player()
    : life_(kLifeStart), score_(kLifeStart), guess_history_(),
      elapsed_time_(0.0) {
  SetDifficulty(1);
}

bool Player::IsGameFinished() const {
  return GetLife() == 0 || (!GetGuesses().empty() &&
                            GetGuesses().back().first == GetSecretCode());
}

void Player::DecrementLife() { --life_; }

void Player::DecrementHint() { --hint_count_; }

void Player::StartTime() {
  start_time_ = std::chrono::high_resolution_clock::now();
}

void Player::EndTime() {
  end_time_ = std::chrono::high_resolution_clock::now();
}

void Player::SaveElapsedTime() {
  std::chrono::duration<double> elapsed = end_time_ - start_time_;
  elapsed_time_ = std::round(elapsed.count() * 1000.0) / 1000.0;
}

void Player::AddToGuessHistory(const std::vector<int> &guess) {
  // if guess is not in history
  if (std::find_if(guess_history_.begin(), guess_history_.end(),
                   [&guess](const std::pair<std::vector<int>, std::string> &p) {
                     return p.first == guess;
                   }) == guess_history_.end()) {
    last_feedback_ =
        player::GiveFeedback(GetSecretCode(), guess, GetSecretCodeLength());
    guess_history_.push_back(std::make_pair(guess, last_feedback_));
  }
}

void Player::AddToHintHistory(const std::string &hint) {
  hint_history_.push_back(hint);
}
} // namespace player
