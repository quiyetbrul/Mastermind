/**
 * @file saved_games.h
 * @brief Declaration of all SavedGames functions.
 */

#ifndef DATA_MANAGEMENT_SAVED_GAMES_H_
#define DATA_MANAGEMENT_SAVED_GAMES_H_

#include <SQLiteCpp/SQLiteCpp.h>
#include <string>

#include "database_manager.h"
#include "player/player.h"

namespace data_management {
/**
 * @class SavedGames
 * @brief Represents the saved games in the game.
 *
 * The SavedGames class manages the saved games.
 */
class SavedGames : public DatabaseManager {
public:
  /**
   * @brief Default constructor.
   */
  SavedGames();

  /**
   * @brief Saves the player's game to the database.
   *
   * @param player The player whose game needs to be saved.
   */
  void Save(const std::string& new_game_name,const player::Player &player);

  /**
   * @brief Deletes the player's game from the saved games.
   *
   * @param player The player whose game needs to be deleted.
   */
  void Delete(const std::string &game_name);

  /**
   * @brief Prints the saved games.
   */
  void PrintGames() const;

protected:
  void CreateTable(const std::string &table_name) override;

private:
  SQLite::Database db_;

  /**
   * @brief Inserts a player into the saved games.
   *
   * @param player The player to be inserted.
   */
  void Insert(const std::string &new_game_name, const player::Player &player);

  /**
   * @brief Updates the saved games with the player's score.
   *
   * @param lowest_score The lowest score in the saved games.
   * @param player The player whose score needs to be updated.
   */
  void Update(const std::string &game_name_to_update,
              const std::string &new_game_name, const player::Player &player);

  /**
   * @brief Gets the number of records in the saved games.
   *
   * @return int The number of records in the saved games.
   */
  int GetCount() const;
};
} // namespace data_management

#endif // DATA_MANAGEMENT_SAVED_GAMES_H_
