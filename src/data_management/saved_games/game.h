/**
 * @file game.h
 * @brief Declaration of all Game functions.
 */

#ifndef DATA_MANAGEMENT_SAVED_GAMES_GAME_H_
#define DATA_MANAGEMENT_SAVED_GAMES_GAME_H_

#include <SQLiteCpp/SQLiteCpp.h>

#include "data_management/saved_games/saved_games.h"
#include "player/player.h"

namespace data_management {
/**
 * @class Game
 * @brief Represents the saved games in the game.
 *
 * The Game class manages the saved games.
 */
class Game : public SavedGames {
public:
  /**
   * @brief Default constructor.
   */
  Game();

  /**
   * @brief Saves the player's game to the database.
   *
   * @param player The player whose game needs to be saved.
   */
  void Save(player::Player &player);

  /**
   * @brief Deletes the player's game from the saved games.
   *
   * @param player The player whose game needs to be deleted.
   */
  void Delete(const int &game_id);

  /**
   * @brief Prints the saved games.
   */
  void PrintGames() const;

private:
  int limit_ = 3;

  int GetSaveLimit() const;
};
} // namespace data_management

#endif // DATA_MANAGEMENT_SAVED_GAMES_GAME_H_
