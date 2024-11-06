/**
 * @file saved_games_handler.cpp
 * @brief Implementation of the SavedGamesHandler class
 */

#include "saved_games_handler.h"

namespace data_management {
std::unordered_map<std::string, player::QuickGame>
SavedGamesHandler::GetSavedGames() const {
  std::unordered_map<std::string, player::QuickGame> saved_games;

  return saved_games;
}

void SavedGamesHandler::SaveGame(
    const std::unordered_map<std::string, player::QuickGame> &players) {}

void SavedGamesHandler::DeleteGame(const std::string &game_name_to_delete) {}
} // namespace data_management
