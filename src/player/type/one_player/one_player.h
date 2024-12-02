/**
 * @file one_player.h
 * @brief Declaration of the OnePlayer class derived from Player.
 */

#ifndef PLAYER_TYPE_ONE_PLAYER_ONE_PLAYER_H_
#define PLAYER_TYPE_ONE_PLAYER_ONE_PLAYER_H_

#include "data_management/scoreboard/score.h"
#include "player/player.h"

#include <ncurses.h>

namespace player {
/**
 * @class OnePlayer
 * @brief Represents a one player game.
 *
 * The OnePlayer class manages the user's one player attributes.
 */
class OnePlayer : public player::Player {
public:
  /**
   * @brief Default constructor.
   *
   * Initializes the one player game with default values.
   */
  OnePlayer(){};

  /**
   * @brief Starts the game.
   *
   * Sets up the one player game, and calls the GameLoop().
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

#endif // PLAYER_TYPE_ONE_PLAYER_ONE_PLAYER_H_
