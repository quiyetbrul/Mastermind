/**
 * @file scoreboard.cpp
 * @brief Implementation of all Scoreboard functions.
 */

#include "scoreboard.h"

#include <iostream>

namespace data_management {
const int kTopScoreLimit = 10;

Scoreboard::Scoreboard()
    : db_(MASTERMIND_DATA, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {
  logger_.Log("Initializing Scoreboard");
  CreateTable("SCOREBOARD");
}

void Scoreboard::Save(const player::Player &player) {
  SQLite::Statement lowest_score = GetLowestScore();
  if (GetCount() >= kTopScoreLimit &&
      player.GetScore() < lowest_score.getColumn("SCORE").getInt()) {
    return;
  }

  std::cout << "You made it to the scoreboard!" << std::endl;
  logger_.Log("You made it to the scoreboard!");

  if (GetCount() >= kTopScoreLimit) {
    Update(lowest_score, player);
    return;
  }

  Insert(player);
}

// TODO: format output
void Scoreboard::PrintScores() const {
  if (GetCount() < 1) {
    std::cout << "No scores yet!" << std::endl;
    return;
  }
  std::cout << "Scoreboard" << std::endl;
  std::cout << "Name\tScore\tTime\tDifficulty" << std::endl;
  SQLite::Statement query(db_, "SELECT * FROM " + GetTableName() +
                                   " ORDER BY SCORE DESC, ELAPSED_TIME ASC;");
  while (query.executeStep()) {
    std::cout << query.getColumn("USER_NAME").getText() << " \t "
              << query.getColumn("SCORE").getInt() << " \t "
              << query.getColumn("ELAPSED_TIME").getDouble() << "s \t "
              << query.getColumn("DIFFICULTY").getInt() << std::endl;
  }
}

void Scoreboard::Insert(const player::Player &player) {
  SQLite::Statement insert(
      db_,
      "INSERT OR REPLACE INTO " + GetTableName() +
          "(USER_NAME, SCORE, ELAPSED_TIME, DIFFICULTY) VALUES(?, ?, ?, ?);");
  insert.bind(1, player.GetName());
  insert.bind(2, player.GetScore());
  insert.bind(3, player.GetElapsedTime());
  insert.bind(4, player.GetDifficulty());
  insert.exec();
}

void Scoreboard::Update(const SQLite::Statement &lowest_score,
                        const player::Player &player) {
  SQLite::Statement update(
      db_, "UPDATE " + GetTableName() +
               " SET USER_NAME = ?, SCORE = ?, ELAPSED_TIME = ? WHERE ID = ?;");
  update.bind(1, player.GetName());
  update.bind(2, player.GetScore());
  update.bind(3, player.GetElapsedTime());
  update.bind(4, player.GetDifficulty());
  update.bind(4, lowest_score.getColumn("ID").getInt());
  update.exec();
}

SQLite::Statement Scoreboard::GetLowestScore() const {
  SQLite::Statement query(
      db_, "SELECT * FROM " + GetTableName() +
               " ORDER BY SCORE ASC, ELAPSED_TIME DESC LIMIT 1;");
  query.executeStep();
  return query;
}

int Scoreboard::GetCount() const {
  SQLite::Statement query(db_, "SELECT COUNT(*) FROM " + GetTableName());
  query.executeStep();
  return query.getColumn(0).getInt();
}

void Scoreboard::CreateTable(const std::string &table_name) {
  SetTableName(table_name);
  db_.exec("CREATE TABLE IF NOT EXISTS " + table_name +
           "(ID INTEGER PRIMARY KEY AUTOINCREMENT, "
           "USER_NAME TEXT NOT NULL, "
           "SCORE INT NOT NULL, "
           "ELAPSED_TIME REAL NOT NULL, "
           "DIFFICULTY INT NOT NULL);");
}
} // namespace data_management
