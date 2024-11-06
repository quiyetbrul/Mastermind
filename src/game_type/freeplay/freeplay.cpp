/**
 * @file freeplay.cpp
 * @brief Implementation of the Freeplay class.
 */

#include "freeplay.h"

#include <iostream>

#include "data_management/scoreboard/scoreboard.h"
#include "logger/logger.h"
#include "player/util/util.h"
#include "ui/banner.h"
#include "util/util.h"

namespace game_type {
void Freeplay::Start() {
  Logger::GetInstance().Log("Starting player's freeplay game");
  Title();

  int user_input = InputInteger(
      "Enter difficulty (1: easy, 2: medium, 3: hard): ", kEasyDifficulty,
      kHardDifficulty);
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
void Freeplay::GameLoop() {
  SetName(InputString("Enter your name: "));
  std::cout << "Welcome, " << GetName() << "!" << std::endl;
  player::PrintCode(GetSecretCode());
  StartTime();

  std::vector<int> guess;
  while (guess != GetSecretCode()) {
    std::cout << "Life: " << GetLife() << std::endl;
    guess =
        player::InputGuess("Enter your guess: ", GetSecretCodeLength(),
                           GetSecretCodeMinDigit(), GetSecretCodeMaxDigit());
    std::cout << DELETE_LINE;

    if (guess == GetSecretCode()) {
      EndTime();
      SaveElapsedTime();
      Congratulations();
      SetScore(GetLife());
      player::PrintSolvedSummary(GetSecretCode(), GetGuesses().size(),
                                 GetElapsedTime());
      game_data::Scoreboard scoreboard_;
      scoreboard_.SaveScore(*this);
      break;
    }

    AddToGuessHistory(guess);
    player::PrintGuess(guess, GetLastFeedBack());
    DecrementLife();

    char give_hint = InputChar("Want a hint? (y/n): ", 'y', 'n');
    if (give_hint == 'y') {
      std::string hint = player::GiveHint(guess, GetSecretCode());
      std::cout << "Hint: " << hint << std::endl;
      AddToHintHistory(hint);
    }

    // TODO: add a way to exit the game
  }
}
} // namespace game_type
