#include "game_state/game_state.h"

/**
 * @brief A Mastermind game clone in C++
 * @author Quiyet Brul
 *
 * @return Returns 0 when execution is successful
 */
int main() {
  mastermind::GameState play;
  play.Init();
  play.Start();

  return 0;
}
