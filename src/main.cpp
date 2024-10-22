#include "gameplay/gameplay.h"
#include "util/util.h"

/**
 * @brief A Mastermind game clone in C++
 *
 * @return Returns 0 when execution is successful
 */
int main() {
  SetTerminalSize();
  SetTerminalTitle("Mastermind Game by Quiyet Brul");

  // TODO: CSVHandler and JSONHandler should be singleton
  // these instances will be passed to the gameplay
  Gameplay gameplay;
  gameplay.Start();

  return 0;
}
