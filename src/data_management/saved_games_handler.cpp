#include "saved_games_handler.h"

#include "player/single/single.h"

std::unordered_map<std::string, player::Single> SavedGamesHandler::GetSavedGames() const {
  std::unordered_map<std::string, player::Single> saved_games;

  return saved_games;
}

void SavedGamesHandler::SaveGame(const player::Player &player) {
    
}
