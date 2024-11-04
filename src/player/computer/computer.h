/**
 * @file computer.h
 * @brief Declaration of the Computer class
 */

#ifndef PLAYER_COMPUTER_H_
#define PLAYER_COMPUTER_H_

#include "player/player.h"

namespace player {
/**
 * @class Computer
 * @brief Represents a computer player in the game.
 *
 * The Computer class manages the computer player's attributes.
 */
class Computer : public Player {
public:
  /**
   * @brief Default constructor.
   *
   * Initializes the computer player with default values.
   */
  Computer(){};

  /**
   * @brief Starts the game.
   *
   * Sets up the computer player and the game, and calls the GameLoop().
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

#endif // PLAYER_COMPUTER_H_
