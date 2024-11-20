/**
 * @file single.h
 * @brief Declaration of the Single class derived from Player.
 */

#ifndef PLAYER_TYPE_SINGLE_SINGLE_H_
#define PLAYER_TYPE_SINGLE_SINGLE_H_

#include "data_management/scoreboard/score.h"
#include "player/player.h"

#include <ncurses.h>

namespace player {
/**
 * @class Single
 * @brief Represents a single player game.
 *
 * The Single class manages the user's single player attributes.
 */
class Single : public player::Player {
public:
  /**
   * @brief Default constructor.
   *
   * Initializes the single player game with default values.
   */
  Single(){};

  /**
   * @brief Starts the game.
   *
   * Sets up the single player game, and calls the GameLoop().
   */
  void Start() override;

  /**
   * @brief Main game loop.
   *
   * Loops through the game until the player runs out of life or solves the
   * code.
   */
  void GameLoop() override;

  // void SetWindow(WINDOW *window);

private:
  data_management::Score score_;
  // WINDOW *window_;
};
} // namespace player

#endif // PLAYER_TYPE_SINGLE_SINGLE_H_
