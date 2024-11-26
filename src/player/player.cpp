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
    : game_id_(-1), life_(kMaxLife), score_(kMaxLife), elapsed_time_(0.0),
      difficulty_(1) {}

bool Player::IsGameFinished() const {
  return GetLife() == 0 || (!GetGuesses().empty() &&
                            GetGuesses().back().first == GetSecretCode());
}

void Player::DecrementLife() { --life_; }

void Player::DecrementHint() { --hint_count_; }

void Player::StartTimeLapse() {
  start_time_lapse_ = std::chrono::high_resolution_clock::now();
}

void Player::EndTimeLapse() {
  end_time_lapse_ = std::chrono::high_resolution_clock::now();
}

void Player::SaveElapsedTime() {
  std::chrono::duration<double> elapsed = end_time_lapse_ - start_time_lapse_;
  elapsed_time_ = std::round(elapsed.count() * 1000.0) / 1000.0;
}

void Player::AddToGuessHistory(const std::vector<int> &guess) {
  auto it =
      std::find_if(guess_history_.begin(), guess_history_.end(),
                   [&guess](const std::pair<std::vector<int>, std::string> &p) {
                     return p.first == guess;
                   });

  if (it == guess_history_.end()) {
    last_feedback_ =
        player::GiveFeedback(GetSecretCode(), guess, GetSecretCodeLength());
  } else {
    last_feedback_ = it->second;
  }

  guess_history_.push_back(std::make_pair(guess, last_feedback_));

  logger_.Log("GUESS HISTORY: ");
  for (const auto &guess : guess_history_) {
    std::string guess_str;
    for (const auto &digit : guess.first) {
      guess_str += std::to_string(digit);
    }
    guess_str += " -> " + guess.second;
    logger_.Log(guess_str);
  }
}

void Player::AddToHintHistory(const std::string &hint) {
  hint_history_.push_back(hint);
}
} // namespace player
