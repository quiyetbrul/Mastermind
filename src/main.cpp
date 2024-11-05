#include "game_state/game_state.h"
#include "logger/logger.h"

/**
 * @brief A Mastermind game clone in C++
 * @author Quiyet Brul
 *
 * @return Returns 0 when execution is successful
 */
int main() {
  Logger::GetInstance().SetOutputFile(LOGGER_FILE_PATH);
  Logger::GetInstance().Log("Starting application");
  mastermind::GameState play;
  play.Init();
  play.Start();

  return 0;
}
