/**
 * @file saved_games.h
 * @brief Declaration of the SavedGames class
 */

#ifndef DATA_MANAGEMENT_SAVED_GAMES_SAVED_GAMES_H_
#define DATA_MANAGEMENT_SAVED_GAMES_SAVED_GAMES_H_

#include <unordered_map>

#include "player/single/single.h"
#include "saved_games_handler.h"

namespace game_data {
/**
 * @class SavedGames
 * @brief Represents the saved games in the game.
 *
 * The SavedGames class manages the saved games in the game. It saves the
 * player's progress, loads the saved game, and deletes the saved game if
 * needed.
 */
class SavedGames {
public:
  /**
   * @brief Default constructor.
   */
  SavedGames();

  /**
   * @brief Initializes the saved games.
   */
  void Init();

  // TODO: make player::Player abstract class a shared pointer
  /**
   * @brief Saves the player's progress.
   *
   * @param game_name The name of the game to save.
   * @param player The player's progress to save.
   */
  void SaveGame(const std::string &game_name, const player::QuickGame &player);

  /**
   * @brief Loads the saved game.
   *
   * @param game_name The name of the game to load.
   * @return The loaded player's progress.
   */
  player::QuickGame LoadGame(const std::string &game_name);

  /**
   * @brief Deletes the saved game.
   */
  void DeleteGame();

  /**
   * @brief Checks if the game is present in the saved games.
   *
   * @param game_name The name of the game to check.
   * @return True if the game is present, false otherwise.
   */
  bool IsGamePresent(const std::string &game_name) const;

  /**
   * @brief Prints the saved games.
   */
  void PrintSavedGames();

private:
  data_management::SavedGamesHandler handler_;
  std::unordered_map<std::string, player::QuickGame> saved_games_;
  const int kMaxSavedGames = 5;

  /**
   * @brief Overwrites the game with the same name.
   *
   * @param game_name The name of the game to overwrite.
   * @param player The player's progress to overwrite.
   */
  void OverwriteGame(const std::string &game_name,
                     const player::QuickGame &player);
};
} // namespace game_data

#endif // DATA_MANAGEMENT_SAVED_GAMES_SAVED_GAMES_H_
