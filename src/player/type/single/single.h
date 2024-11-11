/**
 * @file single.h
 * @brief Declaration of the Single class derived from Player.
 */

#ifndef PLAYER_TYPE_SINGLE_SINGLE_H_
#define PLAYER_TYPE_SINGLE_SINGLE_H_

#include "data_management/scoreboard/score.h"
#include "player/player.h"

namespace player {
/**
 * @class Single
 * @brief Represents a quick game.
 *
 * The Single class manages the user's single player attributes.
 */
class Single : public player::Player {
public:
  /**
   * @brief Default constructor.
   *
   * Initializes the quick game with default values.
   */
  Single(){};

  /**
   * @brief Starts the game.
   *
   * Sets up the quick_game, and calls the GameLoop().
   */
  void Start() override;

  /**
   * @brief Main game loop.
   *
   * Loops through the game until the player runs out of life or solves the
   * code.
   */
  void GameLoop() override;

private:
  data_management::Score score_;
};
} // namespace player

#endif // PLAYER_TYPE_SINGLE_SINGLE_H_
