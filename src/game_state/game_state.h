/**
 * @file game_state.h
 * @brief Declaration of GameState class.
 */

#ifndef GAMESTATE_GAMESTATE_H_
#define GAMESTATE_GAMESTATE_H_

#include "data_management/scoreboard/score.h"
#include "load_game/load_game.h"
#include "logger/logger.h"

#include <ncurses.h>

namespace mastermind {

/**
 * @class GameState
 * @brief Represents the game state.
 *
 * The GameState class manages transitions between different game states.
 */
class GameState {
public:
  /**
   * @brief Default constructor.
   */
  GameState();

  /**
   * @brief Starts the game.
   */
  void Start();

private:
  int y_max_;
  int x_max_;
  WINDOW *banner_window_;
  WINDOW *game_window_;

  game_loader::LoadGame load_;
  data_management::Score score_;

  Logger &logger_ = Logger::GetInstance();

  /**
   * @brief Player's game menu.
   */
  void PlayerMenu();

  /**
   * @brief Load game menu.
   */
  void LoadGameMenu();

  /**
   * @brief Scoreboard.
   */
  void Scoreboard();

  /**
   * @brief Game instructions.
   */
  void Instructions();
};
} // namespace mastermind

#endif // GAMESTATE_GAMESTATE_H_
