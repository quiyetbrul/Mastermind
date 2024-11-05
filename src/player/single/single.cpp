/**
 * @file single.cpp
 * @brief Implementation of the Single class.
 */

#include "single.h"

#include <iostream>

#include "data_management/scoreboard/scoreboard.h"
#include "player/util/util.h"
#include "ui/banner.h"
#include "util/util.h"
#include "logger/logger.h"

namespace player {
void Single::Start() {
  Logger::GetInstance().Log("Starting single player game");
  Title();

  int user_input = InputInteger(
      "Enter difficulty (1: easy, 2: medium, 3: hard): ", kEasyDifficulty,
      kHardDifficulty);
  std::cout << DELETE_LINE;
  SetDifficulty(user_input);

  std::map<std::vector<int>, std::string> user_guess_history;
  SetSecretCode(GenRandom(GetSecretCodeLength(), GetSecretCodeMinDigit(),
                          GetSecretCodeMaxDigit()));
  SetGuesses(user_guess_history);

  GameLoop();
}

// TODO: can be tested
// if winner, save score, else saved_scores_ stays the same
// requires is winner in player
void Single::GameLoop() {
  // TODO: only letters
  SetName(InputString("Enter your name: "));
  std::cout << DELETE_LINE;
  std::cout << "Welcome, " << GetName() << "!" << std::endl;

  StartTime();

  std::vector<int> guess;
  while (GetLife() > 0) {
    std::cout << "Life: " << GetLife() << std::endl;
    guess =
        player::InputGuess("Enter your guess: ", GetSecretCodeLength(),
                           GetSecretCodeMinDigit(), GetSecretCodeMaxDigit());
    std::cout << DELETE_LINE;
    std::cout << DELETE_LINE;

    if (guess == GetSecretCode()) {
      EndTime();
      SaveElapsedTime();
      Congratulations();
      SetScore(GetLife());
      PrintCode(GetSecretCode());
      // TODO: turn into function
      std::cout << "Solved in " << guess_history_.size() << " guesses and "
                << GetElapsedTime() << " seconds." << std::endl;
      game_data::Scoreboard scoreboard_;
      scoreboard_.SaveScore(*this);
      break;
    }

    feedback_ =
        guess_history_
            .try_emplace(guess, player::GiveFeedback(GetSecretCode(), guess,
                                                     GetSecretCodeLength()))
            .first->second;

    PrintGuess(guess, feedback_);
    DecrementLife();

    if (GetLife() == 0) {
      TryAgain();
      PrintCode(GetSecretCode());
      break;
    }
  }
}

} // namespace player
