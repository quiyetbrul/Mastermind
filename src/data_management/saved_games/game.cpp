/**
 * @file game.cpp
 * @brief Implementation of all SavedGames functions.
 */

#include "game.h"

#include <SQLiteCpp/Column.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include <nlohmann/json.hpp>

#include "ui/ui.h"
#include "util/util.h"

namespace data_management {
const int kSaveGameLimit = 3;

Game::Game() : save_limit_(kSaveGameLimit) {}

void Game::Save(player::Player &player) {
  PrintHL(GetWindow());

  int y = 0;
  int x = getmaxx(GetWindow());
  x /= 2;
  std::string title = "Saving Game";
  mvwprintw(GetWindow(), y++, x - (title.length() / 2), "%s", title.c_str());

  // Game was saved before, update it
  if (player.GetGameId() != -1) {
    logger_.Log("Updating game");
    Update(player.GetGameId(), player);
    return;
  }

  // Game was not saved before, prompt user to enter game name
  if (player.GetGameId() == -1) {
    std::string game_name = InputString(GetWindow(), y, "Enter game name: ");
    while (GetCount(game_name) > 0) {
      game_name = InputString(GetWindow(), y,
                              "Game name already exists. Enter game name: ");
    }
    player.SetGameName(game_name);
  }

  // Game was not saved before and limit is reached, ask user to overwrite
  if (GetCount() >= save_limit_) {
    int game_to_replace = SelectGame("Game limit reached. Overwrite a game?");
    if (game_to_replace == -1) {
      logger_.Log("Game not saved");
      return;
    }
    Update(game_to_replace, player);
    logger_.Log("Game overwritten");
    wclear(GetWindow());
    wrefresh(GetWindow());
    return;
  }

  // Game was not saved before and limit is not reached, insert it
  Insert(player);
  logger_.Log("Game saved");
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

  SQLite::Statement query(db_, "SELECT * FROM " + GetTableName() + ";");
  std::vector<std::string> saved_games;

  while (query.executeStep()) {
    saved_games.push_back(query.getColumn("GAME_NAME").getText());
  }
  saved_games.push_back("Back");

  int highlight = 0;

  while (true) {
    UserChoice(GetWindow(), highlight, saved_games, menu_title);
    if (saved_games[highlight] == "Back") {
      return -1;
    }
    SQLite::Statement query(db_, "SELECT ID FROM " + GetTableName() +
                                     " WHERE GAME_NAME = ?;");
    query.bind(1, saved_games[highlight]);
    if (query.executeStep()) {
      game_id = query.getColumn("ID").getInt();
    } else {
      throw std::runtime_error("Game ID not found");
    }
    return game_id;
  }
}
} // namespace data_management
