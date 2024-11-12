/**
 * @file load_game.h
 * @brief Declaration of all LoadGame functions.
 */

#ifndef LOAD_GAME_LOAD_GAME_H_
#define LOAD_GAME_LOAD_GAME_H_

#include "data_management/saved_games/game.h"
#include "player/type/single/single.h"

namespace game_loader {
/**
 * @class LoadGame
 * @brief Represents the saved game loader.
 *
 * The LoadGame class will load the selected game.
 */
class LoadGame : public data_management::Game {
public:
  /**
   * @brief Default constructor.
   */
  LoadGame();

  /**
   * @brief Load the selected game.
   */
  void SelectGame();

  /**
   * @brief Starts the game.
   */
  void Start();

private:
  player::Single player_;
  data_management::Game game_;
  int game_id_;

  int GetGameId();

  void SetGameId(const int &game_id);
};
} // namespace game_loader
#endif // LOAD_GAME_LOAD_GAME_H_
