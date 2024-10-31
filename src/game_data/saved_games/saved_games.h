#ifndef GAME_DATA_SAVED_GAMES_SAVED_GAMES_H_
#define GAME_DATA_SAVED_GAMES_SAVED_GAMES_H_

#include <unordered_map>

#include "data_management/saved_games_handler.h"
#include "player/single/single.h"

namespace game_data {
class SavedGames {
public:
  static SavedGames &GetInstance() {
    static SavedGames instance;
    return instance;
  }

  void SaveGame(const std::string &game_name, const player::Single &player);
  player::Single LoadGame(const std::string &game_name);
  void DeleteGame(const std::string &game_name);
  bool IsGamePresent(const std::string &game_name);
  void PrintSavedGames();

private:
  SavedGames();
  SavedGames(const SavedGames &) = delete;
  SavedGames &operator=(const SavedGames &) = delete;

  SavedGamesHandler handler_;
  std::unordered_map<std::string, player::Single> saved_games_;
  const int kMaxSavedGames = 5;

  void OverwriteGame();
};
} // namespace game_data

#endif // GAME_DATA_SAVED_GAMES_SAVED_GAMES_H_
