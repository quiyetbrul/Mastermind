/**
 * @file load_game.cpp
 * @brief Implementation of all LoadGame functions.
 */

#include "load_game.h"

#include <algorithm>

#include "util/util.h"

namespace game_loader {
LoadGame::LoadGame() {}

void LoadGame::Start() {
  int y;
  int x;
  getmaxyx(window_, y, x);
  y = 1;
  wclear(window_);

  std::string title = "Saved Games";
  mvwprintw(window_, y++, (x / 2) - (title.length() / 2), title.c_str());

  if (GetCount() < 1) {
    std::string no_saved_games = "No saved games yet!";
    mvwprintw(window_, y++, (x / 2) - (no_saved_games.length() / 2),
              no_saved_games.c_str());
    EnterToContinue(window_, y);
    return;
  }
  SelectGame(y);
  SetGame();
  player_.GameLoop();
  if (player_.IsGameFinished()) {
    Delete(GetGameId());
  }
}

int LoadGame::GetGameId() { return game_id_; }

void LoadGame::SetGame() {
  SQLite::Statement query(
      db_, "SELECT GAME_NAME, USER_NAME, LIFE, SECRET_CODE, GUESS_HISTORY, "
           "SCORE, START_TIME, END_TIME, ELAPSED_TIME, HINT_COUNT, "
           "HINT_HISTORY, DIFFICULTY FROM " +
               GetTableName() + " WHERE ID = ?");
  query.bind(1, game_id_);

  if (query.executeStep()) {
    player_.SetGameName(query.getColumn(0).getText());
    player_.SetPlayerName(query.getColumn(1).getText());
    player_.SetLife(query.getColumn(2).getInt());
    player_.SetSecretCode(ConvertToArray<int>(query.getColumn(3).getText()));
    player_.SetGuesses(ConvertToArray<std::pair<std::vector<int>, std::string>>(
        query.getColumn(4).getText()));
    player_.SetScore(query.getColumn(5).getInt());
    player_.SetStartTime(query.getColumn(6).getDouble());
    player_.SetEndTime(query.getColumn(7).getDouble());
    player_.SetElapsedTime(query.getColumn(8).getDouble());
    player_.SetHintCount(query.getColumn(9).getInt());
    player_.SetHintHistory(
        ConvertToArray<std::string>(query.getColumn(10).getText()));
    player_.SetDifficulty(query.getColumn(11).getInt());
  } else {
    // Handle the case where the game to load was not found
    throw std::runtime_error("Game to load not found");
  }
}

void LoadGame::SelectGame(int &y) {
  // TODO: needed?
  int _;
  int x;
  getmaxyx(window_, _, x);
  x = 2;

  int game_id = 0;

  SQLite::Statement query(db_, "SELECT * FROM " + GetTableName() + ";");
  std::vector<std::pair<std::string, int>> saved_games;

  while (query.executeStep()) {
    saved_games.push_back(
        std::make_pair(query.getColumn("GAME_NAME").getText(),
                       query.getColumn("DIFFICULTY").getInt()));
  }

  SQLite::Statement longest_name_query(
      db_, "SELECT GAME_NAME FROM " + GetTableName() +
               " ORDER BY LENGTH(GAME_NAME) DESC LIMIT 1;");
  int longest_name_length = 5;
  if (longest_name_query.executeStep()) {
    longest_name_length = std::max(
        longest_name_length,
        static_cast<int>(strlen(longest_name_query.getColumn(0).getText())));
  }

  std::string header[] = {"Game", "Difficulty"};
  for (const auto &head : header) {
    mvwprintw(window_, y++, x, head.c_str());
    x += (longest_name_length + 2);
  }

  int choice = 0;
  int highlight = 0;
  x = 2; // reset

  while (true) {
    wrefresh(window_);
    for (int i = 0; i < saved_games.size(); ++i) {
      if (highlight == i) {
        wattron(window_, A_STANDOUT);
        mvwprintw(window_, y, x, saved_games[i].first.c_str());
        mvwprintw(window_, y, x + (longest_name_length + 2),
                  std::to_string(saved_games[i].second).c_str());
        wattroff(window_, A_STANDOUT);
      } else {
        mvwprintw(window_, y, x, saved_games[i].first.c_str());
        mvwprintw(window_, y, x + (longest_name_length + 2),
                  std::to_string(saved_games[i].second).c_str());
      }
      ++y;
    }

    choice = wgetch(window_);
    switch (choice) {
    case KEY_UP:
      UpdateHighlight(highlight, saved_games, -1);
      break;
    case KEY_DOWN:
      UpdateHighlight(highlight, saved_games, 1);
      break;
    case 10:
      SQLite::Statement query(db_, "SELECT ID FROM " + GetTableName() +
                                       " WHERE GAME_NAME = ?;");
      query.bind(1, saved_games[highlight].first);
      if (query.executeStep()) {
        game_id = query.getColumn("ID").getInt();
        SetGameId(game_id);
      } else {
        throw std::runtime_error("Game ID not found");
      }
      return;
    }
  }
}

void LoadGame::SetGameId(const int &game_id) { game_id_ = game_id; }

} // namespace game_loader
