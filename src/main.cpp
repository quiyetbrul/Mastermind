#include "gameplay/gameplay.h"
#include "util/util.h"

const int TERMINAL_WIDTH = 125;
const int TERMINAL_HEIGHT = 24;

/**
 * @brief A Mastermind game clone in C++
 *
 * @return Returns 0 when execution is successful
 */
int main() {
  SetTerminalSize(TERMINAL_WIDTH, TERMINAL_HEIGHT);
  SetTerminalTitle("Mastermind Game by Quiyet Brul");

  Gameplay gameplay;
  gameplay.Start();

  return 0;
}
