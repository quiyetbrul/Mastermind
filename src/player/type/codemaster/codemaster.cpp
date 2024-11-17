/**
 * @file codemaster.cpp
 * @brief Implementation of the Codemaster class.
 */

#include "codemaster.h"

#include <string>

#include "player/type/codemaster/codebreaker/codebreaker.h"
#include "player/util/util.h"
#include "util/util.h"

namespace player {
void Codemaster::Start() {
  logger_.Log("Starting computer as codebreaker game");
  wclear(window_);
  wrefresh(window_);

  int highlight = InputDifficulty(window_);
  if (highlight == 3) {
    return;
  }
  SetDifficulty(highlight + 1);
  // SetSecretCode(
  //     InputGuess("Enter your secret code: ", GetSecretCodeLength(),
  //                        GetSecretCodeMinDigit(), GetSecretCodeMaxDigit()));
  SetSecretCode(GenRandom(GetSecretCodeLength(), GetSecretCodeMinDigit(),
                          GetSecretCodeMaxDigit()));
  GameLoop();
}

// TODO: stress test; requires is winner in player
void Codemaster::GameLoop() {
  std::vector<int> guess = {0, 0, 1, 1};
  Codebreaker computer(GetSecretCodeLength(), GetSecretCodeMinDigit(),
                       GetSecretCodeMaxDigit());
  int y;
  int x;
  getmaxyx(window_, y, x);
  box(window_, 0, 0);
  y = 0;
  StartTime();
  while (GetLife() > 0) {
    AddToGuessHistory(guess);
    PrintGuess(window_, y, x, guess, GetLastFeedBack());

    if (guess == GetSecretCode()) {
      EndTime();
      SaveElapsedTime();
      SetScore(GetLife());
      init_pair(1, COLOR_GREEN, COLOR_BLACK);
      PrintSolvedSummary(window_, y, x, GetGuesses().size(), GetElapsedTime());
      init_pair(1, COLOR_CYAN, COLOR_BLACK);
      break;
    }

    DecrementLife();

    if (GetLife() == 0) {
      init_pair(1, COLOR_RED, COLOR_BLACK);
      PrintCode(window_, y, x, GetSecretCode());
      init_pair(1, COLOR_CYAN, COLOR_BLACK);
      break;
    }

    computer.RemoveCode(guess);
    computer.FilterSolutions(guess, GetLastFeedBack());
    guess = computer.MakeGuess();
  }
  EnterToContinue(window_, y);
}

void Codemaster::SetWindow(WINDOW *window) { window_ = window; }
} // namespace player
