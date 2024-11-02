#include "computer.h"

#include <iostream>
#include <string>
#include <thread>

#include "player/computer/codebreaker/codebreaker.h"
#include "player/util/util.h"
#include "ui/banner.h"
#include "util/util.h"

namespace player {
void Computer::Start() {
  Title();

  int user_input = RandomNumber(static_cast<int>(Difficulty::EASY),
                                static_cast<int>(Difficulty::HARD));
  std::cout
      << "Computer is choosing difficulty level (1: easy, 2: medium, 3: hard)"
      << std::endl;
  std::cout << "Difficulty level: " << user_input << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(2));
  std::cout << DELETE_LINE;
  std::cout << DELETE_LINE;
  SetDifficulty(static_cast<Difficulty>(user_input));

  std::map<std::vector<int>, std::string> computer_guess_history;
  SetSecretCode(GenRandom(GetSecretCodeLength(), GetSecretCodeMinDigit(),
                          GetSecretCodeMaxDigit()));
  SetGuesses(computer_guess_history);

  GameLoop();
}

void Computer::GameLoop() {
  std::vector<int> guess = {0, 0, 1, 1};
  player::Codebreaker computer(GetSecretCodeLength(), GetSecretCodeMinDigit(),
                               GetSecretCodeMaxDigit());
  while (GetLife() > 0) {
    if (guess == GetSecretCode()) {
      Congratulations();
      SetScore(GetLife());
      PrintCode(GetSecretCode());
      break;
    }

    feedback_ =
        guess_history_
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

    computer.RemoveCode(guess);
    computer.PruneCodes(guess, feedback_);
    guess = computer.MakeGuess();
  }
}
} // namespace player
