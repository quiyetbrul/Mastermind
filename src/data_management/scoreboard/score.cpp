/**
 * @file score.cpp
 * @brief Implementation of all Scoreboard functions.
 */

#include "score.h"

#include "ui/ui.h"

#include <SQLiteCpp/SQLiteCpp.h>

namespace data_management {
const int kTopScoreLimit = 10;

Score::Score() {}

void Score::Save(const player::Player &player) {
  SQLite::Statement lowest_score = GetLowestScore();
  if (GetCount() >= kTopScoreLimit &&
      player.GetScore() < lowest_score.getColumn("SCORE").getInt()) {
    return;
  }

  if (GetCount() >= kTopScoreLimit) {
    Update(lowest_score, player);
    return;
  }

  Insert(player);
}

void Score::PrintScores() const {
  wclear(GetWindow());
  PrintHL(GetWindow());
  int y = 0;
  int x = getmaxx(GetWindow());
  x /= 2;

  std::string title = "Top Scores";
  mvwprintw(GetWindow(), y++, x - (title.length() / 2), "%s", title.c_str());

  if (GetCount() < 1) {
    std::string no_score = "No scores yet!";
    mvwprintw(GetWindow(), y++, x - (no_score.length() / 2), "%s",
              no_score.c_str());
  } else {
    // Determine the maximum length of user names
    SQLite::Statement max_length_query(
        db_, "SELECT USER_NAME FROM " + GetTableName() +
                 " ORDER BY LENGTH(USER_NAME) DESC LIMIT 1;");
    max_length_query.executeStep();
    int longest_name_length = max_length_query.getColumn("USER_NAME").getInt();
    int col_width = longest_name_length + x;
    int temp = x;

    std::vector<std::string> header = {"Name", "Score", "Time", "Difficulty"};
    PrintHeader(GetWindow(), y, header, longest_name_length);

    int total_width = header.size() * longest_name_length;

    SQLite::Statement query(
        db_, "SELECT * FROM " + GetTableName() +
                 " ORDER BY SCORE DESC, DIFFICULTY DESC, ELAPSED_TIME ASC;");
    while (query.executeStep()) {
      temp = x;
      temp += col_width;
      mvwprintw(GetWindow(), y, (temp / 4) + total_width, "%s",
                query.getColumn("USER_NAME").getText());
      temp += col_width;
      mvwprintw(GetWindow(), y, (temp / 4) + total_width, "%d",
                query.getColumn("SCORE").getInt());
      temp += col_width;
      mvwprintw(GetWindow(), y, (temp / 4) + total_width, "%.2fs",
                query.getColumn("ELAPSED_TIME").getDouble());
      temp += col_width;
      mvwprintw(GetWindow(), y, (temp / 4) + total_width, "%d",
                query.getColumn("DIFFICULTY").getInt());
      ++y;
    }
  }
  wrefresh(GetWindow());
  EnterToContinue(GetWindow(), y);
}
} // namespace data_management
