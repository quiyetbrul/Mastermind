/**
 * @file scoreboard.cpp
 * @brief Implementation of all Scoreboard functions.
 */

#include "score.h"

#include <iostream>

#include <SQLiteCpp/SQLiteCpp.h>

namespace game_data {
const int kTopScoreLimit = 10;

Score::Score() {}

void Score::Save(const player::Player &player) {
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
void Score::PrintScores() const {
  if (GetCount() < 1) {
    std::cout << "No scores yet!" << std::endl;
    return;
  }
  std::cout << "Score" << std::endl;
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
} // namespace game_data
