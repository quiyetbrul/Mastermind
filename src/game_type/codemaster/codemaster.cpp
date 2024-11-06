/**
 * @file codemaster.cpp
 * @brief Implementation of the Codemaster class.
 */

#include "codemaster.h"

#include <string>

#include "game_type/codemaster/codebreaker/codebreaker.h"
#include "logger/logger.h"
#include "player/util/util.h"
#include "ui/banner.h"
#include "util/util.h"

namespace game_type {
void Codemaster::Start() {
  Logger::GetInstance().Log("Starting computer as codebreaker game");
  Title();

  std::map<std::vector<int>, std::string> computer_guess_history;
  // TODO: ask user for secret code instead of using Random.org
  SetSecretCode(GenRandom(GetSecretCodeLength(), GetSecretCodeMinDigit(),
                          GetSecretCodeMaxDigit()));
  SetGuesses(computer_guess_history);

  GameLoop();
}

// TODO: stress test; requires is winner in player
void Codemaster::GameLoop() {
  std::vector<int> guess = {0, 0, 1, 1};
  game_type::Codebreaker computer(
      GetSecretCodeLength(), GetSecretCodeMinDigit(), GetSecretCodeMaxDigit());
  StartTime();
  while (GetLife() > 0) {
    if (guess == GetSecretCode()) {
      EndTime();
      SaveElapsedTime();
      Congratulations();
      SetScore(GetLife());
      player::PrintSolvedSummary(GetSecretCode(), GetGuesses().size(),
                                 GetElapsedTime());
      break;
    }

    AddToGuessHistory(guess);
    player::PrintGuess(guess, GetLastFeedBack());
    DecrementLife();

    if (GetLife() == 0) {
      TryAgain();
      player::PrintCode(GetSecretCode());
      break;
    }

    computer.RemoveCode(guess);
    computer.FilterSolutions(guess, GetLastFeedBack());
    guess = computer.MakeGuess();
  }
}
} // namespace game_type
