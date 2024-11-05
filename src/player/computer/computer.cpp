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

// TODO: stress test; requires is winner in player
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
      PrintSolvedSummary(GetSecretCode(), GetGuesses().size(),
                         GetElapsedTime());
      break;
    }

    AddToGuessHistory(guess);
    PrintGuess(guess, GetLastFeedBack());
    DecrementLife();

    if (GetLife() == 0) {
      TryAgain();
      PrintCode(GetSecretCode());
      break;
    }

    computer.RemoveCode(guess);
    computer.FilterSolutions(guess, GetLastFeedBack());
    guess = computer.MakeGuess();
  }
}
} // namespace player
