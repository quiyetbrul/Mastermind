#include "gameplay.h"

#include <vector>

#include "../menu/menu.h"
#include "../util/util.h"

const int kMinSecretCode = 0;
const int kMaxSecretCodeDigit = 7;
const int kSecretCodeLength = 4;

void Gameplay::Start() {
  int menuChoice = Menu();
  switch (menuChoice) {
    Game();
  case 1:
    break;
  case 2:
    Instructions();
    // TODO: Add a prompt to go back to the main menu
    break;
  case 3:
    Goodbye();
    closeTerminal();
    break;
  }
}

void Gameplay::Game() {
  std::vector<int> secretCode;
  srand(time(0));
  for (int i = 0; i < kSecretCodeLength; i++) {
    secretCode.push_back(gen_random(kMinSecretCode, kMaxSecretCodeDigit));
  }
}
