/**
 * @file game.cpp
 * @brief Implementation of all SavedGames functions.
 */

#include "game.h"

#include <SQLiteCpp/Column.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include <nlohmann/json.hpp>

#include "util/util.h"

namespace data_management {
Game::Game() {}

void Game::Save(player::Player &player) {
  // Game was saved before, update it
  if (!player.GetGameName().empty() && Exists(player.GetGameName())) {
    Update(player.GetGameName(), player.GetGameName(), player);
    return;
  }

  // Game was not saved before, prompt user to enter game name
  if (player.GetGameName().empty()) {
    player.SetGameName(InputString("Enter game name: "));
  }

  // Game was not saved before and limit is reached, ask user to overwrite
  if (GetCount() >= GetSaveLimit()) {
    // TODO: it's easier for user to enter 1-3 instead of game name
    // PrintGames();
    std::string game_to_replace = player.GetGameName();
    while (!Exists(game_to_replace)) {
      game_to_replace =
          InputString("Enter the name of the game to overwrite: ");
    }
    Update(game_to_replace, player.GetGameName(), player);
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

void Game::PrintGames() const {
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
  } else {
    // Determine the maximum length of game names
    SQLite::Statement max_length_query(
        db_, "SELECT MAX(LENGTH(GAME_NAME)) AS max_length FROM " +
                 GetTableName() + ";");
    max_length_query.executeStep();
    int max_game_name_length =
        max_length_query.getColumn("max_length").getInt();

    // Define the headers
    std::string header[] = {"Game Name", "Difficulty"};

    // Print the headers
    int col_width =
        max_game_name_length +
        4; // Column width based on max game name length with some padding
    x = 2; // Starting x position for printing

    for (const auto &head : header) {
      mvwprintw(window_, y, x, head.c_str());
      x += col_width;
    }
    ++y; // Move to the next line for the data

    // Query to get the games
    SQLite::Statement query(db_, "SELECT * FROM " + GetTableName() + ";");
    while (query.executeStep()) {
      x = 2; // Reset x position for each row
      mvwprintw(window_, y, x, "%s", query.getColumn("GAME_NAME").getText());
      x += col_width;
      mvwprintw(window_, y, x, "%d", query.getColumn("DIFFICULTY").getInt());
      ++y;
    }
  }
  EnterToContinue(window_, y);
  return;
}

int Game::GetSaveLimit() const { return limit_; }

void Game::SetWindow(WINDOW *window) { window_ = window; }
} // namespace data_management
