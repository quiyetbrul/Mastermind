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
  x /= 2;
  wclear(window_);
  std::string title = "Top Scores";
  mvwprintw(window_, y++, x - (title.length() / 2), title.c_str());
  if (GetCount() < 1) {
    std::string no_score = "No scores yet!";
    mvwprintw(window_, y++, x - (no_score.length() / 2), no_score.c_str());
  } else {
    // Determine the maximum length of user names
    SQLite::Statement max_length_query(
        db_, "SELECT USER_NAME FROM " + GetTableName() +
                 " ORDER BY LENGTH(USER_NAME) DESC LIMIT 1;");
    max_length_query.executeStep();
    int max_name_length = max_length_query.getColumn("USER_NAME").getInt();

    int col_width = max_name_length + x;

    int temp = x;
    std::vector<std::string> header = {"Name", "Score", "Time", "Difficulty"};
    // TODO: can probably refactor this to a function
    int total_width = header.size() * max_name_length;
    for (const auto &head : header) {
      temp += col_width;
      mvwprintw(window_, y, (temp / 4) + total_width, head.c_str());
    }
    ++y;

    SQLite::Statement query(db_, "SELECT * FROM " + GetTableName() +
                                     " ORDER BY SCORE DESC, ELAPSED_TIME ASC;");
    while (query.executeStep()) {
      temp = x;
      temp += col_width;
      mvwprintw(window_, y, (temp / 4) + total_width, "%s",
                query.getColumn("USER_NAME").getText());
      temp += col_width;
      mvwprintw(window_, y, (temp / 4) + total_width, "%d",
                query.getColumn("SCORE").getInt());
      temp += col_width;
      mvwprintw(window_, y, (temp / 4) + total_width, "%.2fs",
                query.getColumn("ELAPSED_TIME").getDouble());
      temp += col_width;
      mvwprintw(window_, y, (temp / 4) + total_width, "%d",
                query.getColumn("DIFFICULTY").getInt());
      ++y;
    }
  }

  EnterToContinue(window_, y);
}

void Score::SetWindow(WINDOW *window) { window_ = window; }
} // namespace data_management
