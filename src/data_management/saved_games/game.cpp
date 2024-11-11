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

void Game::Save(const std::string &new_game_name,
                const player::Player &player) {
  if (GetCount() >= 3) {
    std::string game_to_replace =
        !Exists(new_game_name)
            ? new_game_name
            : InputString("Enter the name of the game to overwrite: ");
    Update(game_to_replace, new_game_name, player);
    return;
  }
  Insert(new_game_name, player);
}

void Game::Delete(const std::string &game_name) {
  SQLite::Statement query(db_, "DELETE FROM " + GetTableName() +
                                   " WHERE GAME_NAME = ?;");
  query.bind(1, game_name);
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
} // namespace data_management
