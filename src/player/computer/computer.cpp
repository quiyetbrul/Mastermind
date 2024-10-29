#include "computer.h"

#include "player/computer/codebreaker/codebreaker.h"
#include "ui/print.h"
#include "util/util.h"

namespace player {
void Computer::Start() {
  Title();

  std::vector<std::pair<std::vector<int>, std::string>> computer_guess_history;
  SetSecretCode(
      GenRandom(kSecretCodeLength, kMinSecretCodeDigit, kMaxSecretCodeDigit));
  SetGuesses(computer_guess_history);

  Codebreaker computer(kSecretCodeLength, kMinSecretCodeDigit,
                       kMaxSecretCodeDigit);
  std::vector<int> computer_guess = {0, 0, 1, 1};

  GameLoop(&computer, computer_guess);
}
} // namespace player
