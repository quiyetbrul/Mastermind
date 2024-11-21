/**
 * @file codemaster.h
 * @brief Declaration of the Codemaster class
 */

#ifndef PLAYER_TYPE_CODEMASTER_CODEMASTER_H_
#define PLAYER_TYPE_CODEMASTER_CODEMASTER_H_

#include "player/player.h"

#include <ncurses.h>

namespace player {
/**
 * @class Codemaster
 * @brief Represents user as codemaster and computer as codebreaker in the game.
 *
 */
class Codemaster : public player::Player {
public:
  /**
   * @brief Default constructor.
   */
  Codemaster(){};

  /**
   * @brief Starts the game.
   *
   * Sets up the the game, and calls the GameLoop().
   */
  void Start() override;

  void SetWindow(WINDOW *window) { window_ = window; }

private:
  WINDOW *window_;

  /**
   * @brief Main game loop.
   *
   * Loops through the game until the player runs out of life or solves the
   * code.
   */
  void GameLoop() override;
};
} // namespace player

#endif // PLAYER_TYPE_CODEMASTER_CODEMASTER_H_
