/**
 * @file saved_games.cpp
 * @brief Implementation of all SavedGames functions.
 */

#include "saved_games.h"

#include <SQLiteCpp/SQLiteCpp.h>
#include <nlohmann/json.hpp>

#include "util/util.h"

namespace data_management {
SavedGames::SavedGames()
    : db_(MASTERMIND_DATA, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {
  logger_.Log("Initializing SavedGames");
  CreateTable("SAVED_GAMES");
}

void SavedGames::Save(const std::string &new_game_name,
                      const player::Player &player) {
  if (GetCount() >= 3) {
    std::string game_to_replace =
        InputString("Enter the name of the game to overwrite: ");
    Update(game_to_replace, new_game_name, player);
    return;
  }
  Insert(new_game_name, player);
}

void SavedGames::Delete(const std::string &game_name) {
  SQLite::Statement query(db_, "DELETE FROM " + GetTableName() +
                                   " WHERE GAME_NAME = ?;");
  query.bind(1, game_name);
  query.exec();
}

void SavedGames::PrintGames() const {
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

// TODO: Implement this function
void SavedGames::Insert(const std::string &new_game_name,
                        const player::Player &player) {
  SQLite::Statement insert(db_,
                           "INSERT OR REPLACE INTO " + GetTableName() +
                               "(GAME_NAME, USER_NAME, SCORE, ELAPSED_TIME, "
                               "DIFFICULTY) VALUES(?, ?, ?, ?, ?);");
}

// TODO: Implement this function
void SavedGames::Update(const std::string &game_to_replace,
                        const std::string &new_game_name,
                        const player::Player &player) {
  SQLite::Statement update(
      db_,
      "UPDATE " + GetTableName() +
          " SET GAME_NAME = ?, USER_NAME = ?, SCORE = ?, ELAPSED_TIME = ?, "
          "DIFFICULTY = ? WHERE GAME_NAME = ?;");
  update.bind(1, new_game_name);
  update.bind(2, player.GetName());
  update.bind(3, player.GetScore());
  update.bind(4, player.GetElapsedTime());
  update.bind(5, player.GetDifficulty());
  update.bind(6, game_to_replace);
  update.exec();
}

int SavedGames::GetCount() const {
  SQLite::Statement query(db_, "SELECT COUNT(*) FROM " + GetTableName());
  query.executeStep();
  return query.getColumn(0).getInt();
}

void SavedGames::CreateTable(const std::string &table_name) {
  SetTableName(table_name);
  // TODO: create a function that handles arrays through JSON
  db_.exec("CREATE TABLE IF NOT EXISTS " + table_name +
           "(ID INTEGER PRIMARY KEY AUTOINCREMENT, "
           "USER_NAME TEXT NOT NULL, "
           "LIFE INT NOT NULL, "
           "SECRET_CODE TEXT NOT NULL, "   // ARRAY, JSON
           "GUESS_HISTORY TEXT NOT NULL, " // ARRAY <guess, feedback>, JSON
           "SCORE INT NOT NULL, "
           "START_TIME REAL NOT NULL, "
           "END_TIME REAL NOT NULL, "
           "ELAPSED_TIME REAL NOT NULL, "
           "HINT_COUNT INT NOT NULL, "
           "HINT_HISTORY TEXT NOT NULL, " // ARRAY, JSON
           "DIFFICULTY INT NOT NULL);");
}
} // namespace data_management
