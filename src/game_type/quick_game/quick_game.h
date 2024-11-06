/**
 * @file quick_game.h
 * @brief Declaration of the QuickGame class derived from Player.
 */

#ifndef GAME_TYPE_QUICK_GAME_QUICK_GAME_H_
#define GAME_TYPE_QUICK_GAME_QUICK_GAME_H_

#include "player/player.h"

namespace game_type {
/**
 * @class QuickGame
 * @brief Represents a quick game.
 *
 * The QuickGame class manages the player's quick_game attributes.
 */
class QuickGame : public player::Player {
public:
  /**
   * @brief Default constructor.
   *
   * Initializes the quick game with default values.
   */
  QuickGame(){};

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
};
} // namespace game_type

#endif // GAME_TYPE_QUICK_GAME_QUICK_GAME_H_
