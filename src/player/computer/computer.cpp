#include "computer.h"

#include <string>

#include "player/computer/codebreaker/codebreaker.h"
#include "player/util/util.h"
#include "ui/banner.h"
#include "util/util.h"

namespace player {
void Computer::Start() {
  Title();

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

    guess_history_.try_emplace(
        guess,
        player::GiveFeedback(GetSecretCode(), guess, GetSecretCodeLength()));
    feedback_ = guess_history_.rbegin()->second;

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
