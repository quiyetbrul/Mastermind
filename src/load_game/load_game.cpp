/**
 * @file load_game.cpp
 * @brief Implementation of all LoadGame functions.
 */

#include "load_game.h"

#include "ui/ui.h"

#include <ncurses.h>

namespace game_loader {
LoadGame::LoadGame() {}

void LoadGame::Start() {
  int y = 0;
  int x = getmaxx(window_);
  wclear(window_);
  PrintHL(window_);
  x /= 2;
  std::string title = "Saved Games";
  mvwprintw(window_, y++, x - (title.length() / 2), "%s", title.c_str());

  if (GetCount() < 1) {
    std::string no_saved_games = "No saved games yet!";
    mvwprintw(window_, y++, x - (no_saved_games.length() / 2), "%s",
              no_saved_games.c_str());
    EnterToContinue(window_, y);
    return;
  }

  int selected_game = SelectGame("Select Game");
  if (selected_game == -1) {
    return;
  }
  wclear(window_);
  wrefresh(window_);
  SetGame(selected_game);
  player_.SetWindow(window_);
  player_.GameLoop();
  if (player_.IsGameFinished()) {
    Delete(player_.GetGameId());
    logger_.Log("Game deleted: " + std::to_string(player_.GetGameId()));
  }
}

void LoadGame::SetGame(const int &game_id) {
  SQLite::Statement query(
      db_, "SELECT GAME_NAME, USER_NAME, LIFE, SECRET_CODE, GUESS_HISTORY, "
           "SCORE, START_TIME, END_TIME, ELAPSED_TIME, HINT_COUNT, "
           "HINT_HISTORY, DIFFICULTY FROM " +
               GetTableName() + " WHERE ID = ?");
  query.bind(1, game_id);

  if (query.executeStep()) {
    player_.SetGameId(game_id);
    player_.SetGameName(query.getColumn(0).getText());
    player_.SetPlayerName(query.getColumn(1).getText());
    player_.SetLife(query.getColumn(2).getInt());
    player_.SetSecretCode(ConvertToArray<int>(query.getColumn(3).getText()));
    player_.SetGuesses(ConvertToArray<std::pair<std::vector<int>, std::string>>(
        query.getColumn(4).getText()));
    player_.SetScore(query.getColumn(5).getInt());
    player_.SetStartTimeLapse(query.getColumn(6).getDouble());
    player_.SetEndTimeLapse(query.getColumn(7).getDouble());
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
} // namespace game_loader
