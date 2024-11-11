/**
 * @file codemaster.cpp
 * @brief Implementation of the Codemaster class.
 */

#include "codemaster.h"

#include <string>

#include "logger/logger.h"
#include "player/util/util.h"
#include "player/type/codemaster/codebreaker/codebreaker.h"
#include "ui/banner.h"

namespace player {
void Codemaster::Start() {
  Logger::GetInstance().Log("Starting computer as codebreaker game");
  Title();

  // TODO: set difficulty
  SetSecretCode(
      InputGuess("Enter your secret code: ", GetSecretCodeLength(),
                         GetSecretCodeMinDigit(), GetSecretCodeMaxDigit()));

  GameLoop();
}

// TODO: stress test; requires is winner in player
void Codemaster::GameLoop() {
  std::vector<int> guess = {0, 0, 1, 1};
  Codebreaker computer(GetSecretCodeLength(), GetSecretCodeMinDigit(),
                       GetSecretCodeMaxDigit());
  StartTime();
  while (GetLife() > 0) {
    AddToGuessHistory(guess);
    PrintGuess(guess, GetLastFeedBack());
    DecrementLife();

    if (guess == GetSecretCode()) {
      EndTime();
      SaveElapsedTime();
      Congratulations();
      SetScore(GetLife());
      PrintSolvedSummary(GetSecretCode(), GetGuesses().size(),
                                 GetElapsedTime());
      break;
    }

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
