/**
 * @file quick_game.cpp
 * @brief Implementation of the QuickGame class.
 */

#include "quick_game.h"

#include <iostream>

#include "data_management/scoreboard/scoreboard.h"
#include "logger/logger.h"
#include "player/util/util.h"
#include "ui/banner.h"
#include "util/util.h"

namespace game_type {
void QuickGame::Start() {
  Logger::GetInstance().Log("Starting player's quick game");
  Title();

  SetDifficulty(InputInteger("Enter difficulty (1: easy, 2: medium, 3: hard): ",
                             kEasyDifficulty, kHardDifficulty));

  SetSecretCode(GenRandom(GetSecretCodeLength(), GetSecretCodeMinDigit(),
                          GetSecretCodeMaxDigit()));

  SetName(InputString("Enter your name: "));
  std::cout << DELETE_LINE;
  std::cout << "Welcome, " << GetName() << "!" << std::endl;
  player::PrintCode(GetSecretCode());

  GameLoop();
}

// TODO: can be tested
// if winner, save score, else saved_scores_ stays the same
// requires is winner in player
void QuickGame::GameLoop() {
  StartTime();

  int half_life = GetLife() / 2;
  std::vector<int> guess;

  while (GetLife() > 0) {
    if (GetLife() <= half_life && GetHintCount() > 0 &&
        GetLastFeedBack().size() != GetSecretCodeLength()) {
      char give_hint = InputChar("Want a hint? (y/n): ", 'y', 'n');
      std::cout << DELETE_LINE;
      if (give_hint == 'y') {
        std::string hint = player::GiveHint(guess, GetSecretCode());
        std::cout << "Hint: " << hint << std::endl;
        AddToHintHistory(hint);
        DecrementHint();
      }
    }

    std::cout << "Life: " << GetLife() << std::endl;
    guess =
        player::InputGuess("Enter your guess: ", GetSecretCodeLength(),
                           GetSecretCodeMinDigit(), GetSecretCodeMaxDigit());
    std::cout << DELETE_LINE;
    std::cout << DELETE_LINE;

    AddToGuessHistory(guess);
    player::PrintGuess(guess, GetLastFeedBack());
    DecrementLife();

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

    if (GetLife() == 0) {
      TryAgain();
      player::PrintCode(GetSecretCode());
      break;
    }
  }
}
} // namespace game_type
