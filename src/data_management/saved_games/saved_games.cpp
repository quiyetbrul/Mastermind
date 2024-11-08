/**
 * @file saved_games.cpp
 * @brief Implementation of the SavedGames class
 */

#include "saved_games.h"

#include "util/util.h"
#include <string>

namespace game_data {
SavedGames::SavedGames() : handler_(SAVED_GAMES_FILE_PATH) {}

void SavedGames::Init() { saved_games_ = handler_.GetSavedGames(); }

void SavedGames::SaveGame(const std::string &game_name,
                          const game_type::QuickGame &gameplay) {
  if (saved_games_.size() >= kMaxSavedGames && !IsGamePresent(game_name)) {
    DeleteGame();
  }
  saved_games_[game_name] = gameplay;
  handler_.SaveGame(saved_games_);
}

game_type::QuickGame SavedGames::LoadGame(const std::string &game_name) {
  std::string to_load =
      InputString("Enter the name of the game you want to load: ");
  while (!IsGamePresent(to_load)) {
    to_load = InputString(
        "Game not found. Enter the name of the game you want to load: ");
  }
  return saved_games_[game_name];
}

void SavedGames::DeleteGame() {
  // TODO: create a function for this!
  std::string to_delete =
      InputString("Enter the name of the game you want to delete: ");
  while (!IsGamePresent(to_delete)) {
    to_delete = InputString(
        "Game not found. Enter the name of the game you want to delete: ");
  }
  char continue_delete =
      InputChar("Are you sure you want to delete this game? (y/n): ", 'y', 'n');
  if (continue_delete == 'n') {
    return;
  }
  saved_games_.erase(to_delete);
  handler_.DeleteGame(to_delete);
}

bool SavedGames::IsGamePresent(const std::string &game_name) const {
  return saved_games_.find(game_name) != saved_games_.end();
}

void SavedGames::PrintSavedGames() {
  if (saved_games_.empty()) {
    std::cout << "No saved games" << std::endl;
    return;
  }

  for (const auto &game : saved_games_) {
    std::cout << game.first << std::endl;
  }
}
} // namespace game_data
