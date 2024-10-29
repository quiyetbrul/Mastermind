#include "single.h"

#include "gameplay/util/gameplay_util.h"
#include "ui/print.h"

void SinglePlayer::Start() {
  Title();

  std::vector<std::pair<std::vector<int>, std::string>> user_guess_history;
  player.SetSecretCode(
      GenRandom(kSecretCodeLength, kMinSecretCodeDigit, kMaxSecretCodeDigit));
  player.SetGuesses(user_guess_history);

  PlayGameLoop(player);
}
