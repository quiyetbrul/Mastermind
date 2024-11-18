/**
 * @file single.cpp
 * @brief Implementation of the Single class.
 */

#include "single.h"

#include "data_management/saved_games/game.h"
#include "logger/logger.h"
#include "player/util/util.h"
#include "ui/menu.h"
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

  box(window_, 0, 0);
  mvwprintw(window_, 0, 2, "LIFE: %02d  SETTINGS: %d %d %d %d", GetLife(),
            GetDifficulty(), GetSecretCodeLength(), GetSecretCodeMinDigit(),
            GetSecretCodeMaxDigit());

  std::string name = InputString(window_, 1, "Enter your name: ");
  SetPlayerName(name);

  GameLoop();
}

void Single::GameLoop() {
  std::string input;
  std::vector<int> guess;

  int y = 1;
  int x = getmaxx(window_);
  x /= 2;

  PrintCode(window_, y, x, GetSecretCode());

  StartTime();

  while (GetLife() > 0) {
    wrefresh(window_);
    box(window_, 0, 0);
    mvwprintw(window_, 0, 2, "LIFE: %02d  HINTS: %d  SETTINGS: %d %d %d %d",
              GetLife(), GetHintCount(), GetDifficulty(), GetSecretCodeLength(),
              GetSecretCodeMinDigit(), GetSecretCodeMaxDigit());

    input = player::InputGuess(
        window_, y, x, "Enter your guess: ", GetSecretCodeLength(),
        GetSecretCodeMinDigit(), GetSecretCodeMaxDigit(), true);

    if (input == "s") {
      wclear(window_);
      EndTime();
      int old_time = GetElapsedTime();
      SaveElapsedTime();
      int new_time = GetElapsedTime();
      SetElapsedTime(old_time + new_time);
      SetScore(GetLife());
      data_management::Game saved_games;
      saved_games.SetWindow(window_);
      saved_games.Save(*this);
      init_pair(1, COLOR_CYAN, COLOR_BLACK);
      return;
    }

    if (input == "h") {
      std::string hint = "No available hints!";
      if (!GetGuesses().empty() && GetHintCount() > 0 &&
          GetLastFeedBack().size() != GetSecretCodeLength()) {
        hint = player::GiveHint(guess, GetSecretCode());
        mvwprintw(window_, y++, x - (hint.length() / 2), hint.c_str());
        AddToHintHistory(hint);
        DecrementHint();
      } else {
        mvwprintw(window_, y++, x - (hint.length() / 2), hint.c_str());
      }
      continue;
    }

    if (input == "e") {
      wclear(window_);
      init_pair(1, COLOR_CYAN, COLOR_BLACK);
      return;
    }

    guess = player::ConvertToVector(input);

    AddToGuessHistory(guess);
    PrintGuess(window_, y, x, guess, GetLastFeedBack());

    if (guess == GetSecretCode()) {
      EndTime();
      int old_time = GetElapsedTime();
      SaveElapsedTime();
      int new_time = GetElapsedTime();
      SetElapsedTime(old_time + new_time);
      SetScore(GetLife());
      init_pair(1, COLOR_GREEN, COLOR_BLACK);
      PrintSolvedSummary(window_, y, x, GetGuesses().size(), GetElapsedTime());
      std::string message = "You made it to the scoreboard!";
      logger_.Log(message);
      mvwprintw(window_, y++, x - (message.length() / 2), message.c_str());
      score_.Save(*this);
      break;
    }

    DecrementLife();
    wrefresh(window_);
    if (GetLife() == 0) {
      init_pair(1, COLOR_RED, COLOR_BLACK);
      PrintCode(window_, y, x, GetSecretCode());
      break;
    }
  }
  EnterToContinue(window_, y);
  init_pair(1, COLOR_CYAN, COLOR_BLACK);
}

void Single::SetWindow(WINDOW *window) { window_ = window; }
} // namespace player
