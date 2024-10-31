#include "game_state/game_state.h"
#include "util/util.h"

/**
 * @brief A Mastermind game clone in C++
 *
 * @return Returns 0 when execution is successful
 */
int main() {
  SetTerminalSize();
  SetTerminalTitle("Mastermind Game by Quiyet Brul");

  mastermind::GameState play;
  play.Start();

  return 0;
}
