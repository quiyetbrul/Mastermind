/**
 * @file timed_game.h
 * @brief Declaration of the TimedGame class derived from Player.
 */

#ifndef GAME_TYPE_TIMED_GAME_TIMED_GAME_H_
#define GAME_TYPE_TIMED_GAME_TIMED_GAME_H_

#include "player/player.h"

#include <chrono>

namespace game_type {
/**
 * @class TimedGame
 * @brief Represents a TimedGame game.
 *
 * The TimedGame class manages the player's TimedGame attributes.
 */
class TimedGame : public player::Player {
public:
  /**
   * @brief Default constructor.
   *
   * Initializes the TimedGame with default values.
   */
  TimedGame(){};

  /**
   * @brief Starts the game.
   *
   * Sets up the TimedGame, and calls the GameLoop().
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
  std::chrono::seconds time_limit_ = std::chrono::seconds(100);

  /**
   * @brief Gets the time limit for the game.
   */
  std::chrono::seconds GetTimeLimit();

  /**
   * @brief Sets the time limit for the game.
   *
   * @param seconds The time limit in seconds.
   */
  void SetTimeLimit(const int &seconds);
};
} // namespace game_type

#endif // GAME_TYPE_TIMED_GAME_TIMED_GAME_H_
