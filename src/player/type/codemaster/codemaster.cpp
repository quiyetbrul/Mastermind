/**
 * @file codemaster.cpp
 * @brief Implementation of the Codemaster class.
 */

#include "codemaster.h"

#include <ncurses.h>
#include <string>

#include "player/type/codemaster/codebreaker/codebreaker.h"
#include "ui/ui.h"
#include "util/util.h"

namespace player {
void Codemaster::Start() {
  logger_.Log("Starting computer as codebreaker game");

  int highlight = 0;
  std::vector<std::string> choices = {"Easy", "Medium", "Hard", "Back"};
  UserChoice(GetWindow(), highlight, choices, "Select Game Difficulty");
  if (highlight == 3) {
    return;
  }

  SetDifficulty(highlight + 1);

  int y = 1;
  int x = getmaxx(GetWindow());

  wclear(GetWindow());
  PrintHL(GetWindow());
  mvwprintw(GetWindow(), 0, 2, "SETTINGS: %d %d %d %d", GetDifficulty(),
            GetSecretCodeLength(), GetSecretCodeMinDigit(),
            GetSecretCodeMaxDigit());

  // TODO: switch back to user input
  // std::string input = InputSecretCode(
  //     GetWindow(), y, x, "Enter secret code: ", GetSecretCodeLength(),
  //     GetSecretCodeMinDigit(), GetSecretCodeMaxDigit());
  // SetSecretCode(StringToVector(input));
  SetSecretCode(GenRandom(GetSecretCodeLength(), GetSecretCodeMinDigit(),
                          GetSecretCodeMaxDigit()));
  GameLoop();
}

void Codemaster::GameLoop() {
  std::vector<int> guess = {0, 0, 1, 1};
  Codebreaker computer(GetSecretCodeLength(), GetSecretCodeMinDigit(),
                       GetSecretCodeMaxDigit());
  PrintHL(GetWindow());

  int y = 1;
  int x = getmaxx(GetWindow());
  x /= 2;

  StartTimeLapse();
  while (GetLife() > 0) {
    wrefresh(GetWindow());
    mvwprintw(GetWindow(), 0, 2, "SETTINGS: %d %d %d %d    LIFE: %02d",
              GetDifficulty(), GetSecretCodeLength(), GetSecretCodeMinDigit(),
              GetSecretCodeMaxDigit(), GetLife());
    AddToGuessHistory(guess);
    PrintGuess(GetWindow(), y, x, guess, GetLastFeedBack());

    if (guess == GetSecretCode()) {
      EndTimeLapse();
      SaveElapsedTime();
      SetScore(GetLife());
      init_pair(1, COLOR_GREEN, COLOR_BLACK);
      PrintSolvedSummary(GetWindow(), y, x, GetGuesses().size(),
                         GetElapsedTime());
      break;
    }

    DecrementLife();
    InterpolateColor(GetLife(), GetMaxLife());
    wrefresh(GetWindow());

    if (GetLife() == 0) {
      init_pair(1, COLOR_MASTERMIND, COLOR_BLACK);
      PrintCode(GetWindow(), y, x, GetSecretCode());
      break;
    }

    computer.RemoveCode(guess);
    computer.FilterSolutions(guess, GetLastFeedBack());
    guess = computer.MakeGuess();
  }
  EnterToContinue(GetWindow(), y);
  init_pair(1, COLOR_CYAN, COLOR_BLACK);
}
} // namespace player
