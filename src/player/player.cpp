/**
 * @file player.cpp
 * @brief Implementation of the Player class.
 */

#include "player.h"

#include <algorithm>
#include <cmath>
#include <string>

#include "logger/logger.h"
#include "player/util/util.h"

namespace player {
const int kLifeStart = 10;

const int kEasyMinDigit = 0;
const int kEasyMaxDigit = 7;
const int kEasyCodeLength = 4;

const int kMediumMinDigit = 0;
const int kMediumMaxDigit = 8;
const int kMediumCodeLength = 4;

const int kHardMinDigit = 0;
const int kHardMaxDigit = 9;
const int kHardCodeLength = 4;

Player::Player()
    : life_(kLifeStart), score_(kLifeStart), guess_history_(),
      elapsed_time_(0.0) {
  SetDifficulty(1);
}

Player::Player(int &life, int &score, const std::vector<int> &secret_code,
               std::vector<std::pair<std::vector<int>, std::string>> &guesses)
    : life_(life), score_(score), secret_code_(secret_code),
      guess_history_(guesses), elapsed_time_(0.0) {
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

double Player::GetStartTime() const {
  return start_time_.time_since_epoch().count();
}

double Player::GetEndTime() const {
  return end_time_.time_since_epoch().count();
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

std::string Player::GetPlayerName() const { return player_name_; }

std::string Player::GetGameName() const { return game_name_; }

int Player::GetLife() const { return life_; }

int Player::GetScore() const { return score_; }

int Player::GetSecretCodeMinDigit() const { return secret_code_min_digit_; }

int Player::GetSecretCodeMaxDigit() const { return secret_code_max_digit_; }

int Player::GetSecretCodeLength() const { return secret_code_length_; }

int Player::GetDifficulty() const { return difficulty_; }

std::vector<int> Player::GetSecretCode() const { return secret_code_; }

std::vector<std::pair<std::vector<int>, std::string>>
Player::GetGuesses() const {
  return guess_history_;
}

double Player::GetElapsedTime() const { return elapsed_time_; }

int Player::GetHintCount() const { return hint_count_; }

std::vector<std::string> Player::GetHintHistory() const {
  return hint_history_;
}

std::string Player::GetLastFeedBack() const { return last_feedback_; }

void Player::SetPlayerName(const std::string &name) { player_name_ = name; }

void Player::SetGameName(const std::string &name) { game_name_ = name; }

void Player::SetLife(const int &life) { life_ = life; }

void Player::SetScore(const int &score) { score_ = score; }

void Player::SetStartTime(const double &start_time) {
  start_time_ = std::chrono::time_point<std::chrono::high_resolution_clock>(
      std::chrono::nanoseconds(static_cast<long long>(start_time)));
}

void Player::SetEndTime(const double &end_time) {
  end_time_ = std::chrono::time_point<std::chrono::high_resolution_clock>(
      std::chrono::nanoseconds(static_cast<long long>(end_time)));
}

void Player::SetElapsedTime(const double &elapsed_time) {
  elapsed_time_ = elapsed_time;
}

void Player::SetSecretCodeMinDigit(const int &min_digit) {
  secret_code_min_digit_ = min_digit;
}

void Player::SetSecretCodeMaxDigit(const int &max_digit) {
  secret_code_max_digit_ = max_digit;
}

void Player::SetSecretCodeLength(const int &length) {
  secret_code_length_ = length;
}

void Player::SetSecretCode(const std::vector<int> &secret_code) {
  secret_code_ = secret_code;
}

void Player::SetGuesses(
    const std::vector<std::pair<std::vector<int>, std::string>>
        &guess_history) {
  guess_history_ = guess_history;
}

void Player::SetHintCount(const int &hint_count) { hint_count_ = hint_count; }

void Player::SetHintHistory(const std::vector<std::string> &hint_history) {
  hint_history_ = hint_history;
}

void Player::SetLastFeedBack(const std::string &feedback) {
  last_feedback_ = feedback;
}

void Player::SetDifficulty(const int &difficulty) {
  switch (difficulty) {
  case kEasyDifficulty:
    SetSecretCodeMinDigit(kEasyMinDigit);
    SetSecretCodeMaxDigit(kEasyMaxDigit);
    SetSecretCodeLength(kEasyCodeLength);
    break;
  case kMediumDifficulty:
    SetSecretCodeMinDigit(kMediumMinDigit);
    SetSecretCodeMaxDigit(kMediumMaxDigit);
    SetSecretCodeLength(kMediumCodeLength);
    break;
  case kHardDifficulty:
    SetSecretCodeMinDigit(kHardMinDigit);
    SetSecretCodeMaxDigit(kHardMaxDigit);
    SetSecretCodeLength(kHardCodeLength);
    break;
  }
  logger_.Log("Difficulty set to " + std::to_string(difficulty));
  difficulty_ = difficulty;
}
} // namespace player
