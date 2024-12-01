/**
 * @file saved_games.cpp
 * @brief Implementation of all SavedGames functions.
 */

#include "saved_games.h"

#include <SQLiteCpp/Column.h>
#include <SQLiteCpp/SQLiteCpp.h>

namespace data_management {
SavedGames::SavedGames() {
  logger_.Log("Initializing SavedGames");
  CreateTable("SAVED_GAMES");
}

void SavedGames::CreateTable(const std::string &table_name) {
  SetTableName(table_name);
  db_.exec("CREATE TABLE IF NOT EXISTS " + table_name +
           "(ID INTEGER PRIMARY KEY AUTOINCREMENT, "
           "GAME_NAME TEXT NOT NULL UNIQUE, "
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

void SavedGames::Insert(player::Player &player) {
  SQLite::Statement insert(db_,
                           "INSERT OR REPLACE INTO " + GetTableName() +
                               "("
                               "GAME_NAME, "
                               "USER_NAME, "
                               "LIFE, "
                               "SECRET_CODE, "
                               "GUESS_HISTORY, "
                               "SCORE, "
                               "START_TIME, "
                               "END_TIME, "
                               "ELAPSED_TIME, "
                               "HINT_COUNT, "
                               "HINT_HISTORY, "
                               "DIFFICULTY"
                               ")"
                               "VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?); ");
  BindPlayerParameters(insert, player);
  player.SetGameId(static_cast<int>(db_.getLastInsertRowid()));
  insert.exec();
}

void SavedGames::Update(const int &game_to_replace,
                        const player::Player &player) {
  // Perform the update using the retrieved ID
  SQLite::Statement update(
      db_, "UPDATE " + GetTableName() +
               " SET GAME_NAME = ?,"
               " USER_NAME = ?, "
               " LIFE = ?, "
               " SECRET_CODE = ?, "   // ARRAY, JSON
               " GUESS_HISTORY = ?, " // ARRAY <guess, feedback>, JSON
               " SCORE = ?, "
               " START_TIME = ?, "
               " END_TIME = ?, "
               " ELAPSED_TIME = ?, "
               " HINT_COUNT = ?, "
               " HINT_HISTORY = ?, " // ARRAY, JSON
               " DIFFICULTY = ? "
               " WHERE ID = ?;");
  BindPlayerParameters(update, player);
  update.bind(13, game_to_replace);
  update.exec();
}

bool SavedGames::Exists(const std::string &game_name) const {
  SQLite::Statement query(db_, "SELECT COUNT(*) FROM " + GetTableName() +
                                   " WHERE GAME_NAME = ?;");
  query.bind(1, game_name);
  query.executeStep();
  return query.getColumn(0).getInt() > 0;
}

void SavedGames::BindPlayerParameters(SQLite::Statement &stmt,
                                      const player::Player &player) {
  stmt.bind(1, player.GetGameName());
  stmt.bind(2, player.GetPlayerName());
  stmt.bind(3, player.GetLife());
  stmt.bind(4, ConvertToJson(player.GetSecretCode()));
  stmt.bind(5, ConvertToJson(player.GetGuesses()));
  stmt.bind(6, player.GetScore());
  stmt.bind(7, player.GetStartTimeLapse());
  stmt.bind(8, player.GetEndTimeLapse());
  stmt.bind(9, player.GetElapsedTime());
  stmt.bind(10, player.GetHintCount());
  stmt.bind(11, ConvertToJson(player.GetHintHistory()));
  stmt.bind(12, player.GetDifficulty());
}
} // namespace data_management
