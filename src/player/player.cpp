#include "player.h"

#include "game_data/scoreboard/scoreboard.h"
#include "ui/print.h"
#include "util/util.h"

namespace player {

void Player::GameLoop(Codebreaker *computer, std::vector<int> initial_guess) {
  std::vector<int> guess = initial_guess;

  while (GetLife() > 0) {
    if (!computer) {
      guess = InputGuess("Enter your guess: ");
    }

    if (guess == GetSecretCode()) {
      Congratulations();
      SetScore(GetLife());
      PrintCode(GetSecretCode());
      if (!computer) {
        SetName(InputString("Enter your name: "));
        game_data::Scoreboard::GetInstance().SaveScore(*this);
      }
      break;
    }

    if (guess_history_.find(guess) == guess_history_.end()) {
      feedback_ = GiveFeedback(GetSecretCode(), guess);
      AddGuess(guess, feedback_);
    } else {
      feedback_ = guess_history_[guess];
    }

    std::cout << DELETE_LINE;
    PrintGuess(guess, feedback_);
    DecrementLife();

    if (GetLife() == 0) {
      TryAgain();
      PrintCode(GetSecretCode());
      break;
    }

    if (computer) {
      computer->RemoveCode(guess);
      computer->PruneCodes(guess, feedback_);
      guess = computer->MakeGuess();
    }
  }
}

void Player::DecrementLife() { --life_; }

void Player::AddGuess(const std::vector<int> &guess,
                      const std::string &feedback) {
  guess_history_[guess] = feedback;
}

std::string Player::GetName() const { return name_; }

int Player::GetLife() const { return life_; }

int Player::GetScore() const { return score_; }

std::vector<int> Player::GetSecretCode() const { return secret_code_; }

std::map<std::vector<int>, std::string> Player::GetGuesses() const {
  return guess_history_;
}

void Player::SetName(const std::string &name) { name_ = name; }

void Player::SetLife(const int &life) { life_ = life; }

void Player::SetScore(const int &score) { score_ = score; }

void Player::SetSecretCode(const std::vector<int> &secret_code) {
  secret_code_ = secret_code;
}

void Player::SetGuesses(
    std::map<std::vector<int>, std::string> &guess_history) {
  guess_history_ = guess_history;
}
} // namespace player
