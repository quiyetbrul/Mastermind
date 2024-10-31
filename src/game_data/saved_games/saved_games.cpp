#include "saved_games.h"

#include "util/util.h"
#include <string>

namespace game_data {
// void SavedGames::SaveGame(const std::string &game_name,
//                           const player::Player &player) {
//   std::string game_name_ = game_name;
//   if (saved_games_.size() >= kMaxSavedGames && !IsGamePresent(game_name_)) {
//     OverwriteGame();
//   }
//   saved_games_[game_name] = player;
//   handler_.SaveGame(player);
// }

// void SavedGames::OverwriteGame() {
//   std::string to_delete =
//       InputString("Enter the name of the game you want to overwrite: ");

//   while (!IsGamePresent(to_delete)) {
//     to_delete = InputString(
//         "Game not found. Enter the name of the game you want to overwrite: ");
//   }

//   saved_games_.erase(to_delete);
// }

// player::Player SavedGames::LoadGame(const std::string &game_name) {
//   return saved_games_[game_name];
// }

// void SavedGames::DeleteGame(const std::string &game_name) {
//   saved_games_.erase(game_name);
// }

// void SavedGames::PrintSavedGames() {
//   if (saved_games_.empty()) {
//     std::cout << "No saved games" << std::endl;
//     return;
//   }

//   for (const auto &game : saved_games_) {
//     std::cout << game.first << std::endl;
//   }
// }

} // namespace game_data
