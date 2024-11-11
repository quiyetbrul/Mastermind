/**
 * @file saved_games.cpp
 * @brief Implementation of all SavedGames functions.
 */

#include "saved_games.h"

#include <SQLiteCpp/Column.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include <nlohmann/json.hpp>

namespace data_management {
SavedGames::SavedGames()
    : db_(MASTERMIND_DATA, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {
  logger_.Log("Initializing SavedGames");
  CreateTable("SAVED_GAMES");
}

void SavedGames::CreateTable(const std::string &table_name) {
  SetTableName(table_name);
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

void SavedGames::Insert(const std::string &new_game_name,
                        const player::Player &player) {
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
  BindPlayerParameters(insert, player, new_game_name);
  insert.exec();
}

void SavedGames::Update(const std::string &game_to_replace,
                        const std::string &new_game_name,
                        const player::Player &player) {
  SQLite::Statement update(
      db_, "UPDATE " + GetTableName() +
               "SET GAME_NAME = ?,"
               "USER_NAME = ?, "
               "LIFE = ?, "
               "SECRET_CODE = ?, "   // ARRAY, JSON
               "GUESS_HISTORY = ?, " // ARRAY <guess, feedback>, JSON
               "SCORE = ?, "
               "START_TIME = ?, "
               "END_TIME = ?, "
               "ELAPSED_TIME = ?, "
               "HINT_COUNT = ?, "
               "HINT_HISTORY = ?, " // ARRAY, JSON
               "DIFFICULTY = ?"
               "WHERE GAME_NAME = ?;");
  BindPlayerParameters(update, player, new_game_name);
  update.bind(13, game_to_replace);
  update.exec();
}

int SavedGames::GetCount() const {
  SQLite::Statement query(db_, "SELECT COUNT(*) FROM " + GetTableName());
  query.executeStep();
  return query.getColumn(0).getInt();
}

bool SavedGames::Exists(const std::string &game_name) const {
  SQLite::Statement query(db_, "SELECT COUNT(*) FROM " + GetTableName() +
                                   " WHERE GAME_NAME = ?;");
  query.bind(1, game_name);
  query.executeStep();
  return query.getColumn(0).getInt() > 0;
}

void SavedGames::BindPlayerParameters(SQLite::Statement &stmt,
                                      const player::Player &player,
                                      const std::string &new_game_name) {
  stmt.bind(1, new_game_name);
  stmt.bind(2, player.GetName());
  stmt.bind(3, player.GetLife());
  stmt.bind(4, ConvertToJson(player.GetSecretCode()));
  stmt.bind(5, ConvertToJson(player.GetGuesses()));
  stmt.bind(6, player.GetScore());
  stmt.bind(7, player.GetStartTime());
  stmt.bind(8, player.GetEndTime());
  stmt.bind(9, player.GetElapsedTime());
  stmt.bind(10, player.GetHintCount());
  stmt.bind(11, ConvertToJson(player.GetHintHistory()));
  stmt.bind(12, player.GetDifficulty());
}

template <typename T>
std::string SavedGames::ConvertToJson(const std::vector<T> &vec) const {
  nlohmann::json json_array = vec;
  return json_array.dump();
}

template <typename T>
std::vector<T>
SavedGames::ConvertToArray(const std::string &game_name,
                           const std::string &coloumn_name) const {
  SQLite::Statement query(db_, "SELECT " + coloumn_name + " FROM " +
                                   GetTableName() + " WHERE GAME_NAME = ?");
  query.bind(1, game_name);
  if (query.executeStep()) {
    std::string array_str = query.getColumn(0).getText();
    nlohmann::json json_array = nlohmann::json::parse(array_str);
    return json_array.get<std::vector<T>>();
  }
  return {};
}

template std::string
SavedGames::ConvertToJson<int>(const std::vector<int> &vec) const;

template std::string SavedGames::ConvertToJson<std::string>(
    const std::vector<std::string> &vec) const;

template std::string
SavedGames::ConvertToJson<std::map<std::vector<int>, std::string>>(
    const std::vector<std::map<std::vector<int>, std::string>> &vec) const;

template std::vector<int>
SavedGames::ConvertToArray<int>(const std::string &game_name,
                                const std::string &column_name) const;

template std::vector<std::string>
SavedGames::ConvertToArray<std::string>(const std::string &game_name,
                                        const std::string &column_name) const;

template std::vector<std::map<std::vector<int>, std::string>>
SavedGames::ConvertToArray<std::map<std::vector<int>, std::string>>(
    const std::string &game_name, const std::string &column_name) const;
} // namespace data_management
