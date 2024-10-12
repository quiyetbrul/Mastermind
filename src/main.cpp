#include "gameplay/gameplay.h"
#include "util/util.h"

/**
 * @brief A Mastermind game clone in C++
 *
 * @return Returns 0 when execution is successful
 */
int main() {
  srand(time(0));

  SetTerminalSize();
  SetTerminalTitle("Mastermind Game by Quiyet Brul");

  Gameplay gameplay;
  gameplay.Start();

  return 0;
}
