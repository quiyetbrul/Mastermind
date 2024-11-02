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

  SavedGames(const SavedGames &) = delete;
  SavedGames &operator=(const SavedGames &) = delete;

  // TODO: make player::Player abstract class a shared pointer
  void SaveGame(const std::string &game_name, const player::Single &player);
  player::Single LoadGame(const std::string &game_name);
  void DeleteGame();
  bool IsGamePresent(const std::string &game_name) const;
  void PrintSavedGames();

private:
  SavedGames();

  SavedGamesHandler handler_;
  std::unordered_map<std::string, player::Single> saved_games_;
  const int kMaxSavedGames = 5;

  void OverwriteGame(const std::string &game_name,
                     const player::Single &player);
};
} // namespace game_data

#endif // GAME_DATA_SAVED_GAMES_SAVED_GAMES_H_
