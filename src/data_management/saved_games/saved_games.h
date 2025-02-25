/**
 * @file saved_games.h
 * @brief Declaration of all SavedGames functions.
 */

#ifndef DATA_MANAGEMENT_SAVED_GAMES_SAVED_GAMES_H_
#define DATA_MANAGEMENT_SAVED_GAMES_SAVED_GAMES_H_

#include <string>

#include "data_management/database_manager.h"
#include "player/player.h"

#include <SQLiteCpp/SQLiteCpp.h>
#include <nlohmann/json.hpp>

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
  void CreateTable(const std::string &table_name) override;

  /**
   * @brief Inserts a player into the saved games.
   *
   * @param player The player to be inserted.
   */
  void Insert(player::Player &player);

  /**
   * @brief Updates the saved games with the player's score.
   *
   * @param lowest_score The lowest score in the saved games.
   * @param player The player whose score needs to be updated.
   */
  void Update(const int &game_name_to_update, const player::Player &player);

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
                            const player::Player &player);

public:
  /**
   * @brief Converts a set to a JSON string.
   *
   * @tparam T
   * @param set
   * @return std::string
   */
  template <typename T>
  std::string ConvertToJson(const std::vector<T> &vec) const {
    nlohmann::json json_array = vec;
    return json_array.dump();
  }

  /**
   * @brief Converts a JSON string to a set.
   *
   * @tparam T
   * @param game_name
   * @param coloumn_name
   * @return std::vector<T>
   */
  template <typename T>
  std::vector<T> ConvertToArray(const std::string &json_str) const {
    nlohmann::json json_array = nlohmann::json::parse(json_str);
    return json_array.get<std::vector<T>>();
  }
};
} // namespace data_management

#endif // DATA_MANAGEMENT_SAVED_GAMES_SAVED_GAMES_H_
