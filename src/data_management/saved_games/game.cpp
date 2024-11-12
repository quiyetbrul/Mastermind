/**
 * @file game.cpp
 * @brief Implementation of all SavedGames functions.
 */

#include "game.h"

#include <SQLiteCpp/Column.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include <nlohmann/json.hpp>

#include "util/util.h"

namespace data_management {
Game::Game() {}

void Game::Save(player::Player &player) {
  // Game was saved before, update it
  if (!player.GetGameName().empty() && Exists(player.GetGameName())) {
    Update(player.GetGameName(), player.GetGameName(), player);
    return;
  }

  // Game was not saved before, prompt user to enter game name
  if (player.GetGameName().empty()) {
    player.SetGameName(InputString("Enter game name: "));
  }

  // Game was not saved before and limit is reached, ask user to overwrite
  if (GetCount() >= GetSaveLimit()) {
    // TODO: it's easier for user to enter 1-3 instead of game name
    PrintGames();
    std::string game_to_replace = player.GetGameName();
    while (!Exists(game_to_replace)) {
      game_to_replace =
          InputString("Enter the name of the game to overwrite: ");
    }
    Update(game_to_replace, player.GetGameName(), player);
    return;
  }

  // Game was not saved before and limit is not reached, insert it
  Insert(player);
}

void Game::Delete(const int &game_id) {
  SQLite::Statement query(db_,
                          "DELETE FROM " + GetTableName() + " WHERE ID = ?;");
  query.bind(1, game_id);
  query.exec();
}

void Game::PrintGames() const {
  if (GetCount() < 1) {
    std::cout << "No saved games yet!" << std::endl;
    return;
  }
  std::cout << "Saved Games" << std::endl;
  std::cout << "Game Name\t\t\tDifficulty" << std::endl;
  SQLite::Statement query(db_, "SELECT * FROM " + GetTableName() + ";");
  while (query.executeStep()) {
    std::cout << query.getColumn("GAME_NAME").getText() << " \t\t\t "
              << query.getColumn("DIFFICULTY").getInt() << std::endl;
  }
}

int Game::GetSaveLimit() const { return limit_; }
} // namespace data_management
