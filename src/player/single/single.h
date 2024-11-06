/**
 * @file single.h
 * @brief Declaration of the Single class derived from Player.
 */

#ifndef SINGLE_SINGLE_H_
#define SINGLE_SINGLE_H_

#include "player/player.h"

namespace player {
/**
 * @class Single
 * @brief Represents a single player in the game.
 *
 * The Single class manages the single player's attributes.
 */
class QuickGame : public Player {
public:
  /**
   * @brief Default constructor.
   *
   * Initializes the single player with default values.
   */
  QuickGame(){};

  /**
   * @brief Starts the game.
   *
   * Sets up the single player and the game, and calls the GameLoop().
   */
  void Start() override;

protected:
  /**
   * @brief Main game loop.
   *
   * Loops through the game until the player runs out of life or solves the
   * code.
   */
  void GameLoop() override;
};
} // namespace player

#endif // SINGLE_SINGLE_H_
