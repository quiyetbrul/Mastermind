/**
 * @file game_state.h
 * @brief Declaration of GameState class.
 */

#ifndef GAMESTATE_GAMESTATE_H_
#define GAMESTATE_GAMESTATE_H_

#include "game_data/saved_games/saved_games.h"
#include "game_data/scoreboard/scoreboard.h"
namespace mastermind {

/**
 * @class GameState
 * @brief Represents the game state.
 *
 * The GameState class manages the game state and transitions between different
 * states of the game.
 */
class GameState {
public:
  /**
   * @brief Default constructor.
   */
  GameState(){};

  void Init();

  /**
   * @brief Starts the game.
   */
  void Start();

private:
  game_data::Scoreboard scoreboard_;
  game_data::SavedGames saved_games_;

  /**
   * @brief Main game loop.
   */
  void PlayerMenu();

  /**
   * @brief Player game loop.
   *
   * This function is called at every end of a game. It prompts the user to
   * choose whether to play again and go back to PlayerMenu() or go back to
   * Start().
   */
  void PlayAgain();
};
} // namespace mastermind

#endif // GAMESTATE_GAMESTATE_H_
