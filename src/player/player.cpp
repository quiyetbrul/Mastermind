/**
 * @file player.cpp
 * @brief Implementation of the Player class.
 */

#include "player.h"

#include <cmath>
#include <string>

#include "logger/logger.h"
#include "player/util/util.h"

namespace player {
const int kEasyMinDigit = 0;
const int kEasyMaxDigit = 7;
const int kEasyCodeLength = 4;

const int kMediumMinDigit = 0;
const int kMediumMaxDigit = 8;
const int kMediumCodeLength = 4;

const int kHardMinDigit = 0;
const int kHardMaxDigit = 9;
const int kHardCodeLength = 4;

Player::Player() : life_(kLifeStart), score_(kLifeStart), guess_history_() {
  SetDifficulty(1);
}

Player::Player(int &life, int &score, const std::vector<int> &secret_code,
               std::map<std::vector<int>, std::string> &guesses)
    : life_(life), score_(score), secret_code_(secret_code),
      guess_history_(guesses) {
  SetDifficulty(1);
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
  last_feedback_ =
      guess_history_
          .try_emplace(guess, player::GiveFeedback(GetSecretCode(), guess,
                                                   GetSecretCodeLength()))
          .first->second;
}

std::string Player::GetName() const { return name_; }

int Player::GetLife() const { return life_; }

int Player::GetScore() const { return score_; }

int Player::GetSecretCodeMinDigit() const { return secret_code_min_digit_; }

int Player::GetSecretCodeMaxDigit() const { return secret_code_max_digit_; }

int Player::GetSecretCodeLength() const { return secret_code_length_; }

int Player::GetDifficulty() const { return difficulty_; }

std::vector<int> Player::GetSecretCode() const { return secret_code_; }

std::map<std::vector<int>, std::string> Player::GetGuesses() const {
  return guess_history_;
}

double Player::GetElapsedTime() const { return elapsed_time_; }

int Player::GetHintCount() const { return hint_count_; }

void Player::SetName(const std::string &name) { name_ = name; }

void Player::SetLife(const int &life) { life_ = life; }

void Player::SetScore(const int &score) { score_ = score; }

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
    std::map<std::vector<int>, std::string> &guess_history) {
  guess_history_ = guess_history;
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
  Logger &logger_ = Logger::GetInstance();
  logger_.Log("Difficulty set to " + std::to_string(difficulty));
  difficulty_ = difficulty;
}
} // namespace player
