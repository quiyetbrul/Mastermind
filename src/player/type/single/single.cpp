/**
 * @file single.cpp
 * @brief Implementation of the Single class.
 */

#include "single.h"

#include <iostream>
#include <ncurses.h>

#include "data_management/saved_games/game.h"
#include "logger/logger.h"
#include "player/util/util.h"
#include "util/util.h"

namespace player {
void Single::Start() {
  logger_.Log("Starting single player game");

  int highlight = InputDifficulty(window_);
  if (highlight == 3) {
    return;
  }
  SetDifficulty(highlight + 1);

  SetSecretCode(GenRandom(GetSecretCodeLength(), GetSecretCodeMinDigit(),
                          GetSecretCodeMaxDigit()));

  wclear(window_);
  wrefresh(window_);

  std::string name = InputString(window_, 1, "Enter your name: ");
  SetPlayerName(name);

  GameLoop();
}

// TODO: can be tested
// if winner, save score, else saved_scores_ stays the same
// requires is winner in player
void Single::GameLoop() {

  int half_life = GetLife() / 2;
  std::vector<int> guess;

  int y_max;
  int x_max;
  getmaxyx(window_, y_max, x_max);
  box(window_, 0, 0);
  int y = 1;
  PrintCode(window_, y, x_max, GetSecretCode());
  StartTime();
  while (GetLife() > 0) {
    wrefresh(window_);
    mvwprintw(window_, 0, 2, "LIFE: %02d  HINTS: %d  SETTINGS: %d %d %d %d",
              GetLife(), GetHintCount(), GetDifficulty(), GetSecretCodeLength(),
              GetSecretCodeMinDigit(), GetSecretCodeMaxDigit());

    //
    // if (GetLife() <= half_life && GetHintCount() > 0 &&
    //     GetLastFeedBack().size() != GetSecretCodeLength()) {
    //   char give_hint = InputChar("Want a hint? (y/n): ", 'y', 'n');
    //   std::cout << DELETE_LINE;
    //   if (give_hint == 'y') {
    //     std::string hint = player::GiveHint(guess, GetSecretCode());
    //     std::cout << "Hint: " << hint << std::endl;
    //     AddToHintHistory(hint);
    //     DecrementHint();
    //   }
    // }
    // TODO: it's probably easier to refactor InputGuess to return a string
    // and create a new function to convert it to a vector after if statement
    // for save
    guess = player::InputGuess(
        window_, y, "Enter your guess: ", GetSecretCodeLength(),
        GetSecretCodeMinDigit(), GetSecretCodeMaxDigit());
    // std::string save = InputString("Save guess? (y/n): ");

    // if (save == "y") {
    //   data_management::Game saved_games;
    //   saved_games.Save(*this);
    //   break;
    // }

    AddToGuessHistory(guess);
    PrintGuess(window_, y, x_max, guess, GetLastFeedBack());

    if (guess == GetSecretCode()) {
      EndTime();
      SaveElapsedTime();
      SetScore(GetLife());
      init_pair(1, COLOR_GREEN, COLOR_BLACK);
      PrintSolvedSummary(window_, y, x_max, GetGuesses().size(),
                         GetElapsedTime());
      std::string message = "You made it to the scoreboard!";
      logger_.Log(message);
      mvwprintw(window_, y++, (x_max / 2) - (message.length() / 2),
                message.c_str());
      score_.Save(*this);
      break;
    }

    DecrementLife();
    wrefresh(window_);
    if (GetLife() == 0) {
      init_pair(1, COLOR_RED, COLOR_BLACK);
      PrintCode(window_, y, x_max, GetSecretCode());
      break;
    }
  }
  EnterToContinue(window_, y);
  init_pair(1, COLOR_CYAN, COLOR_BLACK);
}

void Single::SetWindow(WINDOW *window) { window_ = window; }
} // namespace player
