#include "single.h"

#include "game_data/scoreboard/scoreboard.h"
#include "player/util/util.h"
#include "ui/print.h"
#include <iostream>

namespace player {
void Single::Start() {
  Title();

  std::map<std::vector<int>, std::string> user_guess_history;
  SetSecretCode(
      GenRandom(kSecretCodeLength, kMinSecretCodeDigit, kMaxSecretCodeDigit));
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
    guess = InputGuess("Enter your guess: ");
    std::cout << DELETE_LINE;
    std::cout << DELETE_LINE;

    if (guess == GetSecretCode()) {
      Congratulations();
      SetScore(GetLife());
      PrintCode(GetSecretCode());
      game_data::Scoreboard::GetInstance().SaveScore(*this);
      break;
    }

    feedback_ =
        guess_history_.try_emplace(guess, GiveFeedback(GetSecretCode(), guess))
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
