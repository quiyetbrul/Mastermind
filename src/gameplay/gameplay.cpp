#include "gameplay.h"

#include <vector>

#include "../menu/menu.h"
#include "../util/util.h"

const int MIN_SECRET_CODE = 0;
const int MAX_SECRET_CODE = 7;
const int SECRET_CODE_LENGTH = 4;

void Gameplay::gameplay() {
  int menuChoice = menu();
  switch (menuChoice) {
    game();
  case 1:
    break;
  case 2:
    instructions();
    break;
  case 3:
    goodbye();
    closeTerminal();
    break;
  }
}

void Gameplay::game() {
  std::vector<int> secretCode;
  srand(time(0));
  for (int i = 0; i < SECRET_CODE_LENGTH; i++) {
    secretCode.push_back(gen_random(MIN_SECRET_CODE, MAX_SECRET_CODE));
  }
}
