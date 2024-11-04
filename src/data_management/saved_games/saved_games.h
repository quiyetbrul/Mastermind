#ifndef DATA_MANAGEMENT_SAVED_GAMES_SAVED_GAMES_H_
#define DATA_MANAGEMENT_SAVED_GAMES_SAVED_GAMES_H_

#include <unordered_map>

#include "player/single/single.h"
#include "saved_games_handler.h"

namespace game_data {
class SavedGames {
public:
  SavedGames();

  void Init();

  // TODO: make player::Player abstract class a shared pointer
  void SaveGame(const std::string &game_name, const player::Single &player);
  player::Single LoadGame(const std::string &game_name);
  void DeleteGame();
  bool IsGamePresent(const std::string &game_name) const;
  void PrintSavedGames();

private:
  data_management::SavedGamesHandler handler_;
  std::unordered_map<std::string, player::Single> saved_games_;
  const int kMaxSavedGames = 5;

  void OverwriteGame(const std::string &game_name,
                     const player::Single &player);
};
} // namespace game_data

#endif // DATA_MANAGEMENT_SAVED_GAMES_SAVED_GAMES_H_
