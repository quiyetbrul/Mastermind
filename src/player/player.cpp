#include "player.h"

#include "ui/print.h"
#include "util/util.h"

namespace player {

void Player::GameLoop(Codebreaker *computer, std::vector<int> initial_guess) {
  std::vector<int> guess = initial_guess;

  while (GetLife() > 0) {

    if (!computer) {
      guess = InputGuess("Enter your guess: ");
      // TODO: memoize the guess
    }

    if (guess == GetSecretCode()) {
      Congratulations();
      PrintCode(GetSecretCode());
      SetWinner(true);
      break;
    }

    std::string feedback = GiveFeedback(GetSecretCode(), guess);
    AddGuess(guess, feedback);
    PrintGuesses(GetGuesses());
    DecrementLife();

    if (GetLife() == 0) {
      TryAgain();
      PrintCode(GetSecretCode());
      SetWinner(false);
      break;
    }

    if (computer) {
      computer->RemoveCode(guess);           // Remove the guess from the set
      computer->PruneCodes(guess, feedback); // Prune the set of codes
      guess = computer->MakeGuess();         // Use MakeGuess to get a guess
    }
  }
}

std::vector<int> Player::InputGuess(const std::string &prompt) {
  std::string input;
  while (true) {
    std::cout << prompt;
    std::cin >> input;

    if (input.length() != kSecretCodeLength) {
      std::cout << "Input must be exactly " << kSecretCodeLength
                << " digits long." << std::endl;
      continue;
    }

    if (!std::all_of(input.begin(), input.end(),
                     [](char c) { return c >= '0' && c <= '7'; })) {
      std::cout << "Each digit must be between 0 and 7." << std::endl;
      continue;
    }

    break;
  }

  std::vector<int> result(input.begin(), input.end());
  std::transform(result.begin(), result.end(), result.begin(),
                 [](char c) { return c - '0'; });

  return result;
}

void Player::DecrementLife() { --life_; }

void Player::DecrementScore() { --score_; }

void Player::AddGuess(const std::vector<int> &guess,
                      const std::string &feedback) {
  guesses_.push_back(std::make_pair(guess, feedback));
}

std::string Player::GetName() const { return name_; }

int Player::GetLife() const { return life_; }

int Player::GetScore() const { return score_; }

std::vector<int> Player::GetSecretCode() const { return secret_code_; }

std::vector<std::pair<std::vector<int>, std::string>>
Player::GetGuesses() const {
  return guesses_;
}

void Player::SetName(const std::string &name) { name_ = name; }

bool Player::IsWinner() const { return is_winner_; }

void Player::SetLife(const int &life) { life_ = life; }

void Player::SetScore(const int &score) { score_ = score; }

void Player::SetSecretCode(const std::vector<int> &secret_code) {
  secret_code_ = secret_code;
}

void Player::SetGuesses(
    std::vector<std::pair<std::vector<int>, std::string>> &guesses) {
  guesses_ = guesses;
}

void Player::SetWinner(const bool &is_winner) { is_winner_ = is_winner; };
} // namespace player
