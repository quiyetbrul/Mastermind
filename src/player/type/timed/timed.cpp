/**
 * @file timed.cpp
 * @brief Implementation of the OnePlayer class.
 */

#include "timed.h"

#include "logger/logger.h"
#include "player/util/util.h"
#include "ui/ui.h"
#include "util/util.h"

namespace player {
void Timed::Start() {
  logger_.Log("Starting one player game");

  int highlight = 0;
  std::vector<std::string> choices = {"Easy", "Medium", "Hard", "Back"};
  UserChoice(GetWindow(), highlight, choices, "Select Game Difficulty");
  if (highlight == 3) {
    return;
  }
  SetDifficulty(highlight + 1);

  wclear(GetWindow());
  PrintHL(GetWindow());
  mvwprintw(GetWindow(), 0, 2, "SETTINGS: %d %d %d %d", GetDifficulty(),
            GetSecretCodeLength(), GetSecretCodeMinDigit(),
            GetSecretCodeMaxDigit());

  std::string name = InputString(GetWindow(), 1, "Enter your name: ");
  SetPlayerName(name);

  SetSecretCode(GenRandom(GetSecretCodeLength(), GetSecretCodeMinDigit(),
                          GetSecretCodeMaxDigit()));

  GameLoop();
}

void Timed::GameLoop() {
  std::string input;
  std::vector<int> guess;

  PrintHL(GetWindow());

  int y = 1;
  int x = getmaxx(GetWindow());
  x /= 2;

  // TODO: remove before final release
  PrintCode(GetWindow(), y, x, GetSecretCode());

  // TODO: add thread to update time in real-time, both in UI and mechanics
  // (time's up)
  StartTimeLapse();
  int time_limit = 5; // Time limit in seconds (e.g., 5 minutes)

  while (GetLife() > 0) {
    EndTimeLapse();
    SaveElapsedTime();
    int remaining_time = time_limit - GetElapsedTime();
    remaining_time = remaining_time < 0 ? 0 : remaining_time;

    wrefresh(GetWindow());
    mvwprintw(GetWindow(), 0, 2,
              "SETTINGS: %d %d %d %d    LIFE: %02d    [H]INTS: %d    [E]XIT    "
              "TIME: %02d:%02d",
              GetDifficulty(), GetSecretCodeLength(), GetSecretCodeMinDigit(),
              GetSecretCodeMaxDigit(), GetLife(), GetHintCount(),
              remaining_time / 60, remaining_time % 60);

    if (remaining_time <= 0) {
      init_pair(1, COLOR_RED, COLOR_BLACK);
      mvwprintw(GetWindow(), y++, x - 10, "Time's up! You lost.");
      break;
    }

    input = InputSecretCode(GetWindow(), y, x,
                            "Enter your guess: ", GetSecretCodeLength(),
                            GetSecretCodeMinDigit(), GetSecretCodeMaxDigit());

    if (input == "h") {
      std::string hint = "No available hints!";
      if (!GetGuesses().empty() && GetHintCount() > 0 &&
          GetLastFeedBack().size() != GetSecretCodeLength()) {
        hint = player::GiveHint(guess, GetSecretCode());
        AddToHintHistory(hint);
        DecrementHint();
      }
      logger_.Log("Hint: " + hint);
      mvwprintw(GetWindow(), y++, x - (hint.length() / 2), "%s", hint.c_str());
      continue;
    }

    if (input == "e") {
      wclear(GetWindow());
      init_pair(1, COLOR_CYAN, COLOR_BLACK);
      logger_.Log("Exiting game");
      return;
    }

    guess = StringToVector(input);

    AddToGuessHistory(guess);
    PrintGuess(GetWindow(), y, x, guess, GetLastFeedBack());

    if (guess == GetSecretCode()) {
      if (GetGameId() != -1) {
        SaveElapsedTime();
      }
      SaveElapsedTime();
      SetScore(GetLife());
      init_pair(1, COLOR_GREEN, COLOR_BLACK);
      PrintSolvedSummary(GetWindow(), y, x, GetGuesses().size(),
                         GetElapsedTime());
      score_.Save(*this);
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
  }

  EnterToContinue(GetWindow(), y);
  init_pair(1, COLOR_CYAN, COLOR_BLACK);
}
} // namespace player
