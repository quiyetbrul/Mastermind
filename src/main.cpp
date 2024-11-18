#include "game_state/game_state.h"
#include "logger/logger.h"

/**
 * @brief A Mastermind game clone in C++
 * @author Quiyet Brul
 */
int main() {
  Logger &logger = Logger::GetInstance();
  logger.SetOutputFile(LOGGER_FILE_PATH);
  logger.Log("Starting application");

  mastermind::GameState play;
  play.Start();

  return 0;
}
