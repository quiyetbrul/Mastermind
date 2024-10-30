#include "player.h"

#include "game_data/scoreboard/scoreboard.h"
#include "ui/print.h"
#include "util/util.h"

namespace player {

void Player::GameLoop(Codebreaker *computer, std::vector<int> initial_guess) {
  std::vector<int> guess = initial_guess;

  if (!computer) {
    SetName(InputString("Enter your name: "));
  }

  while (GetLife() > 0) {
    if (!computer) {
      guess = InputGuess("Enter your guess: ");
    }

    if (guess == GetSecretCode()) {
      Congratulations();
      SetScore(GetLife());
      PrintCode(GetSecretCode());
      if (!computer) {
        game_data::Scoreboard::GetInstance().SaveScore(*this);
      }
      break;
    }

    feedback_ =
        guess_history_.try_emplace(guess, GiveFeedback(GetSecretCode(), guess))
            .first->second;

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
