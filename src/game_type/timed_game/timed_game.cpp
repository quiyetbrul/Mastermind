/**
 * @file timed_game.cpp
 * @brief Implementation of the TimedGame class.
 */

#include "timed_game.h"

#include <chrono>
#include <iostream>

#include "data_management/scoreboard/scoreboard.h"
#include "logger/logger.h"
#include "player/util/util.h"
#include "ui/banner.h"
#include "util/util.h"

namespace game_type {
void TimedGame::Start() {
  Logger::GetInstance().Log("Starting player's timed game");
  Title();

  int user_input = InputInteger(
      "Enter difficulty (1: easy, 2: medium, 3: hard): ", kEasyDifficulty,
      kHardDifficulty);
  SetDifficulty(user_input);

  std::map<std::vector<int>, std::string> user_guess_history;
  SetSecretCode(GenRandom(GetSecretCodeLength(), GetSecretCodeMinDigit(),
                          GetSecretCodeMaxDigit()));
  SetGuesses(user_guess_history);
  SetTimeLimit(5);

  GameLoop();
}

// TODO: can be tested
// if winner, save score, else saved_scores_ stays the same
// requires is winner in player
// TODO: learn threading
void TimedGame::GameLoop() {
  SetName(InputString("Enter your name: "));
  std::cout << DELETE_LINE;
  std::cout << "Welcome, " << GetName() << "!" << std::endl;
  player::PrintCode(GetSecretCode());
  StartTime();

  int half_life = GetLife() / 2;
  auto start_time = std::chrono::steady_clock::now();
  auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(
      std::chrono::steady_clock::now() - start_time);

  std::vector<int> guess;
  while (elapsed_time < GetTimeLimit()) {
    elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::steady_clock::now() - start_time);

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

    elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::steady_clock::now() - start_time);

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

    if (GetLife() == 0) {
      TryAgain();
      player::PrintCode(GetSecretCode());
      break;
    }
  }
  TryAgain();
  std::cout << "Time's up!" << std::endl;
  player::PrintCode(GetSecretCode());
}

std::chrono::seconds TimedGame::GetTimeLimit() { return time_limit_; }

void TimedGame::SetTimeLimit(const int &seconds) {
  time_limit_ = std::chrono::seconds(seconds);
}
} // namespace game_type
