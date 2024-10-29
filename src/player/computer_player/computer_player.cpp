#include "computer_player.h"

#include "player/computer_player/codebreaker/codebreaker.h"
#include "gameplay/util/gameplay_util.h"
#include "ui/print.h"
#include "util/util.h"

void ComputerPlayer::Start() {
  Title();

  std::vector<std::pair<std::vector<int>, std::string>> computer_guess_history;
  player.SetSecretCode(
      GenRandom(kSecretCodeLength, kMinSecretCodeDigit, kMaxSecretCodeDigit));
  player.SetGuesses(computer_guess_history);

  Codebreaker computer(kSecretCodeLength, kMinSecretCodeDigit,
                       kMaxSecretCodeDigit);
  std::vector<int> computer_guess = {0, 0, 1, 1};

  PlayGameLoop(player, &computer, computer_guess);
}
