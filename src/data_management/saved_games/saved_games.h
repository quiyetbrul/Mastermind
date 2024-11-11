/**
 * @file saved_games.h
 * @brief Declaration of all SavedGames functions.
 */

#ifndef DATA_MANAGEMENT_SAVED_GAMES_SAVED_GAMES_H_
#define DATA_MANAGEMENT_SAVED_GAMES_SAVED_GAMES_H_

#include <SQLiteCpp/SQLiteCpp.h>
#include <string>

#include "data_management/database_manager.h"
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

protected:
  SQLite::Database db_;

  void CreateTable(const std::string &table_name) override;

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

  /**
   * @brief Checks if a game exists in the saved games.
   *
   * @param game_name The name of the game to check.
   * @return bool True if the game exists, false otherwise.
   */
  bool Exists(const std::string &game_name) const;

  /**
   * @brief Binds the player's parameters to a SQLiteCPP statement.
   *
   * @param stmt
   * @param player
   * @param new_game_name
   */
  void BindPlayerParameters(SQLite::Statement &stmt,
                            const player::Player &player,
                            const std::string &new_game_name);

  /**
   * @brief Converts a set to a JSON string.
   *
   * @tparam T
   * @param set
   * @return std::string
   */
  template <typename T>
  std::string ConvertToJson(const std::vector<T> &set) const;

  /**
   * @brief Converts a JSON string to a set.
   *
   * @tparam T
   * @param game_name
   * @param coloumn_name
   * @return std::vector<T>
   */
  template <typename T>
  std::vector<T> ConvertToArray(const std::string &game_name,
                                const std::string &coloumn_name) const;
};
} // namespace data_management

#endif // DATA_MANAGEMENT_SAVED_GAMES_SAVED_GAMES_H_
