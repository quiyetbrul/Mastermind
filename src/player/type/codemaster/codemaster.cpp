/**
 * @file codemaster.cpp
 * @brief Implementation of the Codemaster class.
 */

#include "codemaster.h"

#include <string>

#include "player/type/codemaster/codebreaker/codebreaker.h"
#include "player/util/util.h"
#include "ui/menu.h"

namespace player {
void Codemaster::Start() {
  logger_.Log("Starting computer as codebreaker game");

  int highlight = 0;
  std::vector<std::string> choices = {"Easy", "Medium", "Hard", "Back"};
  UserChoice(window_, highlight, choices, "Select Player Type");
  if (highlight == 3) {
    return;
  }

  SetDifficulty(highlight + 1);

  int y = 1;
  int x = getmaxx(window_);

  wclear(window_);
  PrintHL(window_);
  mvwprintw(window_, 0, 2, "LIFE: %02d  SETTINGS: %d %d %d %d", GetLife(),
            GetDifficulty(), GetSecretCodeLength(), GetSecretCodeMinDigit(),
            GetSecretCodeMaxDigit());

  std::string input = player::InputSecretCode(
      window_, y, x, "Enter secret code: ", GetSecretCodeLength(),
      GetSecretCodeMinDigit(), GetSecretCodeMaxDigit());
  SetSecretCode(player::ConvertToVector(input));

  GameLoop();
}

// TODO: stress test; requires is winner in player
void Codemaster::GameLoop() {
  std::vector<int> guess = {0, 0, 1, 1};
  Codebreaker computer(GetSecretCodeLength(), GetSecretCodeMinDigit(),
                       GetSecretCodeMaxDigit());
  PrintHL(window_);

  int y = 1;
  int x = getmaxx(window_);
  x /= 2;

  StartTime();
  while (GetLife() > 0) {
    wrefresh(window_);
    mvwprintw(window_, 0, 2, "LIFE: %02d  SETTINGS: %d %d %d %d", GetLife(),
              GetDifficulty(), GetSecretCodeLength(), GetSecretCodeMinDigit(),
              GetSecretCodeMaxDigit());
    AddToGuessHistory(guess);
    PrintGuess(window_, y, x, guess, GetLastFeedBack());

    if (guess == GetSecretCode()) {
      EndTime();
      SaveElapsedTime();
      SetScore(GetLife());
      init_pair(1, COLOR_GREEN, COLOR_BLACK);
      PrintSolvedSummary(window_, y, x, GetGuesses().size(), GetElapsedTime());
      break;
    }

    DecrementLife();

    if (GetLife() == 0) {
      init_pair(1, COLOR_RED, COLOR_BLACK);
      PrintCode(window_, y, x, GetSecretCode());
      break;
    }

    computer.RemoveCode(guess);
    computer.FilterSolutions(guess, GetLastFeedBack());
    guess = computer.MakeGuess();
  }
  EnterToContinue(window_, y);
  init_pair(1, COLOR_CYAN, COLOR_BLACK);
}
} // namespace player
