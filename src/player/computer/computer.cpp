/**
 * @file computer.cpp
 * @brief Implementation of the Computer class.
 */

#include "computer.h"

#include <string>

#include "logger/logger.h"
#include "player/computer/codebreaker/codebreaker.h"
#include "player/util/util.h"
#include "ui/banner.h"
#include "util/util.h"

namespace player {
void Computer::Start() {
  Logger::GetInstance().Log("Starting computer player game");
  Title();

  std::map<std::vector<int>, std::string> computer_guess_history;
  SetSecretCode(GenRandom(GetSecretCodeLength(), GetSecretCodeMinDigit(),
                          GetSecretCodeMaxDigit()));
  SetGuesses(computer_guess_history);

  GameLoop();
}

void Computer::GameLoop() {
  std::vector<int> guess = {0, 0, 1, 1};
  player::Codebreaker computer(GetSecretCodeLength(), GetSecretCodeMinDigit(),
                               GetSecretCodeMaxDigit());
  StartTime();
  while (GetLife() > 0) {
    if (guess == GetSecretCode()) {
      EndTime();
      SaveElapsedTime();
      Congratulations();
      SetScore(GetLife());
      PrintCode(GetSecretCode());
      std::cout << "Solved in " << guess_history_.size() << " guesses and "
                << GetElapsedTime() << " seconds." << std::endl;
      break;
    }

    AddToGuessHistory(guess);
    PrintGuess(guess, last_feedback_);
    DecrementLife();

    if (GetLife() == 0) {
      TryAgain();
      PrintCode(GetSecretCode());
      break;
    }

    computer.RemoveCode(guess);
    computer.FilterSolutions(guess, last_feedback_);
    guess = computer.MakeGuess();
  }
}
} // namespace player
