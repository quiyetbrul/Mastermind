#ifndef DATA_MANAGEMENT_GAMEPLAY_HANDLER_H
#define DATA_MANAGEMENT_GAMEPLAY_HANDLER_H

#include <string>
#include <unordered_map>

#include "player/player.h"
#include "player/single/single.h"

class SavedGamesHandler {
public:
  SavedGamesHandler(){};

  SavedGamesHandler(const std::string &file_name) : file_name_(file_name) {}

  std::unordered_map<std::string, player::Single> GetSavedGames() const;

  void SaveGame(const player::Player &player);

private:
  std::string file_name_;
};

#endif // DATA_MANAGEMENT_GAMEPLAY_HANDLER_H
