/**
 * @file game.cpp
 * @brief Implementation of all SavedGames functions.
 */

#include "game.h"

#include <algorithm>

#include <SQLiteCpp/Column.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include <nlohmann/json.hpp>

#include "ui/menu.h"
#include "util/util.h"

namespace data_management {
Game::Game() { limit_ = 3; }

void Game::Save(player::Player &player) {
  PrintHL(window_);

  int y = 0;
  int x = getmaxx(window_);
  x /= 2;
  std::string title = "Saving Game";
  mvwprintw(window_, y++, x - (title.length() / 2), "%s", title.c_str());
  // Game was saved before, update it
  if (!player.GetGameName().empty() && Exists(player.GetGameName())) {
    SQLite::Statement query(db_, "SELECT ID FROM " + GetTableName() +
                                     " WHERE GAME_NAME = ?");
    query.bind(1, player.GetGameName());
    query.executeStep();
    int game_id = query.getColumn(0).getInt();
    Update(game_id, player);
    return;
  }

  // Game was not saved before, prompt user to enter game name
  if (player.GetGameName().empty()) {
    std::string game_name = InputString(window_, y, "Enter game name: ");
    player.SetGameName(game_name);
  }

  // Game was not saved before and limit is reached, ask user to overwrite
  if (GetCount() >= GetSaveLimit()) {
    int game_to_replace = SelectGame("Game limit reached. Overwrite a game?");
    Update(game_to_replace, player);
    wclear(window_);
    wrefresh(window_);
    return;
  }

  // Game was not saved before and limit is not reached, insert it
  Insert(player);
}

void Game::Delete(const int &game_id) {
  SQLite::Statement query(db_,
                          "DELETE FROM " + GetTableName() + " WHERE ID = ?;");
  query.bind(1, game_id);
  query.exec();
}

int Game::SelectGame(const std::string &menu_title) {
  int x = 2;

  int game_id = 0;

  SQLite::Statement max_length_query(
      db_, "SELECT GAME_NAME FROM " + GetTableName() +
               " ORDER BY LENGTH(GAME_NAME) DESC LIMIT 1;");
  int longest_name_length = 5;
  if (max_length_query.executeStep()) {
    longest_name_length = std::max(
        longest_name_length,
        static_cast<int>(strlen(max_length_query.getColumn(0).getText())));
  }

  SQLite::Statement query(db_, "SELECT * FROM " + GetTableName() + ";");
  std::vector<std::string> saved_games;

  while (query.executeStep()) {
    saved_games.push_back(query.getColumn("GAME_NAME").getText());
  }
  saved_games.push_back("Back");

  // std::vector<std::string> header = {"Game", "Difficulty"};
  // PrintHeader(window_, y, header, longest_name_length);

  int highlight = 0;

  while (true) {
    UserChoice(window_, highlight, saved_games, menu_title);
    if (saved_games[highlight] == "Back") {
      return -1;
    }
    SQLite::Statement query(db_, "SELECT ID FROM " + GetTableName() +
                                     " WHERE GAME_NAME = ?;");
    query.bind(1, saved_games[highlight]);
    if (query.executeStep()) {
      game_id = query.getColumn("ID").getInt();
      SetGameId(game_id);
    } else {
      throw std::runtime_error("Game ID not found");
    }
    return game_id;
  }
}

int Game::GetSaveLimit() const { return limit_; }

int Game::GetGameId() { return game_id_; }

void Game::SetWindow(WINDOW *window) { window_ = window; }

void Game::SetGameId(const int &game_id) { game_id_ = game_id; }
} // namespace data_management
