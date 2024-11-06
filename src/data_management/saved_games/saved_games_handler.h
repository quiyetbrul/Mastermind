/**
 * @file saved_games_handler.h
 * @brief Declaration of the SavedGamesHandler class
 */

#ifndef DATA_MANAGEMENT_GAMEPLAY_HANDLER_H
#define DATA_MANAGEMENT_GAMEPLAY_HANDLER_H

#include <string>
#include <unordered_map>

#include "game_type/quick_game/quick_game.h"

namespace data_management {
/**
 * @class SavedGamesHandler
 * @brief Handles the saved games data.
 *
 * The SavedGamesHandler class manages the saved games data. It reads the saved
 * games from a file, updates the saved games with new games, and writes the
 * updated saved games back to the file.
 */
class SavedGamesHandler {
public:
  /**
   * @brief Default constructor.
   */
  SavedGamesHandler(){};

  /**
   * @brief Parameterized constructor.
   * @param file_name The name of the file to read and write the saved games
   * data.
   */
  SavedGamesHandler(const std::string &file_name) : file_name_(file_name) {}

  /**
   * @brief Get the Saved Games object
   *
   * @return std::unordered_map<std::string, player::Single> The saved games.
   */
  std::unordered_map<std::string, game_type::QuickGame> GetSavedGames() const;

  /**
   * @brief Save the game to the saved games data.
   *
   * @param players The players to save.
   */
  void
  SaveGame(const std::unordered_map<std::string, game_type::QuickGame> &players);

  /**
   * @brief Delete the game from the saved games data.
   *
   * @param game_name_to_delete The name of the game to delete.
   */
  void DeleteGame(const std::string &game_name_to_delete);

private:
  std::string file_name_;
};
} // namespace data_management

#endif // DATA_MANAGEMENT_GAMEPLAY_HANDLER_H
