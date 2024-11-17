/**
 * @file single.cpp
 * @brief Implementation of the Single class.
 */

#include "single.h"

#include <iostream>

#include "data_management/saved_games/game.h"
#include "logger/logger.h"
#include "player/util/util.h"
#include "ui/banner.h"
#include "util/util.h"

namespace player {
void Single::Start() {
  logger_.Log("Starting player's quick game");
  Title();

  SetDifficulty(InputInteger("Enter difficulty (1: easy, 2: medium, 3: hard): ",
                             kEasyDifficulty, kHardDifficulty));

  SetSecretCode(GenRandom(GetSecretCodeLength(), GetSecretCodeMinDigit(),
                          GetSecretCodeMaxDigit()));

  SetPlayerName(InputString("Enter your name: "));
  std::cout << DELETE_LINE;
  std::cout << "Welcome, " << GetPlayerName() << "!" << std::endl;
  player::PrintCode(GetSecretCode());

  GameLoop();
}

// TODO: can be tested
// if winner, save score, else saved_scores_ stays the same
// requires is winner in player
void Single::GameLoop() {
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
    // TODO: it's probably easier to refactor InputGuess to return a string
    // and create a new function to convert it to a vector after if statement
    // for save
    guess =
        player::InputGuess("Enter your guess: ", GetSecretCodeLength(),
                           GetSecretCodeMinDigit(), GetSecretCodeMaxDigit());

    std::string save = InputString("Save guess? (y/n): ");

    if (save == "y") {
      data_management::Game saved_games;
      saved_games.Save(*this);
      break;
    }

    // TODO: do string to vector conversion here

    std::cout << DELETE_LINE;
    std::cout << DELETE_LINE;

    AddToGuessHistory(guess);
    player::PrintGuess(guess, GetLastFeedBack());

    if (guess == GetSecretCode()) {
      EndTime();
      SaveElapsedTime();
      Congratulations();
      SetScore(GetLife());
      player::PrintSolvedSummary(GetSecretCode(), GetGuesses().size(),
                                 GetElapsedTime());
      score_.Save(*this);
      break;
    }

    DecrementLife();

    if (GetLife() == 0) {
      TryAgain();
      player::PrintCode(GetSecretCode());
      break;
    }
  }
}
} // namespace player
