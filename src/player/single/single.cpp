#include "single.h"

#include <iostream>

#include "game_data/scoreboard/scoreboard.h"
#include "player/util/util.h"
#include "ui/banner.h"
#include "util/util.h"

namespace player {
void Single::Start() {
  Title();

  int user_input = InputInteger(
      "Enter difficulty (1: easy, 2: medium, 3: hard): ",
      static_cast<int>(Difficulty::EASY), static_cast<int>(Difficulty::HARD));
  std::cout << DELETE_LINE;
  SetDifficulty(static_cast<Difficulty>(user_input));

  std::map<std::vector<int>, std::string> user_guess_history;
  SetSecretCode(GenRandom(GetSecretCodeLength(), GetSecretCodeMinDigit(),
                          GetSecretCodeMaxDigit()));
  SetGuesses(user_guess_history);

  GameLoop();
}

void Single::GameLoop() {
  SetName(InputString("Enter your name: "));
  std::cout << DELETE_LINE;
  std::cout << "Welcome, " << GetName() << "!" << std::endl;

  std::vector<int> guess;
  while (GetLife() > 0) {
    std::cout << "Life: " << GetLife() << std::endl;
    guess = player::InputGuess("Enter your guess: ", GetSecretCodeLength(),
                       GetSecretCodeMinDigit(), GetSecretCodeMaxDigit());
    std::cout << DELETE_LINE;

    if (guess == GetSecretCode()) {
      Congratulations();
      SetScore(GetLife());
      PrintCode(GetSecretCode());
      game_data::Scoreboard::GetInstance().SaveScore(*this);
      break;
    }

    feedback_ = guess_history_
                    .try_emplace(guess, player::GiveFeedback(GetSecretCode(), guess,
                                                     GetSecretCodeLength()))
                    .first->second;

    PrintGuess(guess, feedback_);
    DecrementLife();

    if (GetLife() == 0) {
      TryAgain();
      PrintCode(GetSecretCode());
      break;
    }
  }
}

} // namespace player
