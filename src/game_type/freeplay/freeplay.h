/**
 * @file freeplay.h
 * @brief Declaration of the Freeplay class derived from Player.
 */

#ifndef GAME_TYPE_FREEPLAY_FREEPLAY_H_
#define GAME_TYPE_FREEPLAY_FREEPLAY_H_

#include "player/player.h"

namespace game_type {
/**
 * @class Freeplay
 * @brief Represents a freeplay game.
 *
 * The Freeplay class manages the player's freeplay attributes.
 */
class Freeplay : public player::Player {
public:
  /**
   * @brief Default constructor.
   *
   * Initializes the freeplay with default values.
   */
  Freeplay(){};

  /**
   * @brief Starts the game.
   *
   * Sets up the freeplay, and calls the GameLoop().
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

#endif // GAME_TYPE_FREEPLAY_FREEPLAY_H_
