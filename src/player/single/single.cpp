#include "single.h"

#include "ui/print.h"

namespace player {
void Single::Start() {
  Title();

  std::map<std::vector<int>, std::string> user_guess_history;
  SetSecretCode(
      GenRandom(kSecretCodeLength, kMinSecretCodeDigit, kMaxSecretCodeDigit));
  SetGuesses(user_guess_history);

  GameLoop();
}
} // namespace player
