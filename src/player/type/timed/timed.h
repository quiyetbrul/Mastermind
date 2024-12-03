/**
 * @file timed.h
 * @brief Declaration of the Timed class derived from Player.
 */

#ifndef PLAYER_TYPE_TIMED_TIMED_H_
#define PLAYER_TYPE_TIMED_TIMED_H_

#include "data_management/scoreboard/score.h"
#include "player/player.h"

#include <ncurses.h>

namespace player {
/**
 * @class Timed
 * @brief Represents a timed one player game.
 *
 * The Timed class manages the user's timed one player attributes.
 */
class Timed : public player::Player {
public:
  /**
   * @brief Default constructor.
   *
   * Initializes the timed game with default values.
   */
  Timed(){};

  /**
   * @brief Starts the game.
   *
   * Sets up the timed game, and calls the GameLoop().
   */
  void Start() override;

  /**
   * @brief Main game loop.
   *
   * Loops through the game until the player runs out of life, solves the
   * code,
   */
  void GameLoop() override;

private:
  data_management::Score score_;
};
} // namespace player

#endif // PLAYER_TYPE_TIMED_TIMED_H_
