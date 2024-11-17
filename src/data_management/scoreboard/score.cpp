/**
 * @file score.cpp
 * @brief Implementation of all Scoreboard functions.
 */

#include "score.h"

#include "util/util.h"

#include <SQLiteCpp/SQLiteCpp.h>
#include <ncurses.h>

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
  int y;
  int x;
  getmaxyx(window_, y, x);
  y = 1;
  wclear(window_);
  std::string title = "Top Scores";
  mvwprintw(window_, y++, (x / 2) - (title.length() / 2), title.c_str());
  if (GetCount() < 1) {
    std::string no_score = "No scores yet!";
    mvwprintw(window_, y++, (x / 2) - (no_score.length() / 2),
              no_score.c_str());
  } else {
    // Determine the maximum length of user names
    SQLite::Statement max_length_query(
        db_, "SELECT MAX(LENGTH(USER_NAME)) FROM " + GetTableName() + ";");
    max_length_query.executeStep();
    int max_name_length = max_length_query.getColumn("USER_NAME").getInt();

    std::string header[] = {"Name", "Score", "Time", "Difficulty"};

    x = 2; // Starting x position for printing
    int col_width = max_name_length + x;

    for (const auto &head : header) {
      mvwprintw(window_, y, x, head.c_str());
      x += col_width;
    }
    ++y;

    SQLite::Statement query(db_, "SELECT * FROM " + GetTableName() +
                                     " ORDER BY SCORE DESC, ELAPSED_TIME ASC;");
    while (query.executeStep()) {
      x = 2;
      mvwprintw(window_, y, x, "%s", query.getColumn("USER_NAME").getText());
      x += col_width;
      mvwprintw(window_, y, x, "%d", query.getColumn("SCORE").getInt());
      x += col_width;
      mvwprintw(window_, y, x, "%.2fs",
                query.getColumn("ELAPSED_TIME").getDouble());
      x += col_width;
      mvwprintw(window_, y, x, "%d", query.getColumn("DIFFICULTY").getInt());
      ++y;
    }
  }
  EnterToContinue(window_, y);
}

void Score::SetWindow(WINDOW *window) { window_ = window; }
} // namespace data_management
