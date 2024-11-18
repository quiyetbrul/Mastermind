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
  wclear(window_);
  wrefresh(window_);

  int highlight = InputDifficulty(window_);
  if (highlight == 3) {
    return;
  }
  PrintHL(window_);
  SetDifficulty(highlight + 1);
  int y = 1;
  int x = getmaxx(window_);
  mvwprintw(window_, 0, 2, "LIFE: %02d  SETTINGS: %d %d %d %d", GetLife(),
            GetDifficulty(), GetSecretCodeLength(), GetSecretCodeMinDigit(),
            GetSecretCodeMaxDigit());

  std::string input = player::InputGuess(
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

  int y = 2;
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

void Codemaster::SetWindow(WINDOW *window) { window_ = window; }
} // namespace player
