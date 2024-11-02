#include "player.h"

namespace player {

void Player::DecrementLife() { --life_; }

std::string Player::GetName() const { return name_; }

int Player::GetLife() const { return life_; }

int Player::GetScore() const { return score_; }

int Player::GetSecretCodeMinDigit() const { return secret_code_min_digit_; }

int Player::GetSecretCodeMaxDigit() const { return secret_code_max_digit_; }

int Player::GetSecretCodeLength() const { return secret_code_length_; }

std::vector<int> Player::GetSecretCode() const { return secret_code_; }

std::map<std::vector<int>, std::string> Player::GetGuesses() const {
  return guess_history_;
}

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
} // namespace player
