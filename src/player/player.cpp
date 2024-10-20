#include "player.h"

void Player::DecrementLife() { --life_; }

void Player::DecrementScore() { --score_; }

void Player::AddGuess(const std::vector<int> &guess,
                      const std::string &feedback) {
  guesses_.push_back(std::make_pair(guess, feedback));
}

int Player::GetLife() const { return life_; }

int Player::GetScore() const { return score_; }

std::vector<int> Player::GetSecretCode() const { return secret_code_; }

std::vector<std::pair<std::vector<int>, std::string>>
Player::GetGuesses() const {
  return guesses_;
}

void Player::SetLife(const int &life) { life_ = life; }

void Player::SetScore(const int &score) { score_ = score; }

void Player::SetSecretCode(const std::vector<int> &secret_code) {
  secret_code_ = secret_code;
}

void Player::SetGuesses(
    std::vector<std::pair<std::vector<int>, std::string>> &guesses) {
  guesses_ = guesses;
}
