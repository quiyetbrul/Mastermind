/**
 * @file load_game.cpp
 * @brief Implementation of all LoadGame functions.
 */

#include "load_game.h"

#include "ui/menu.h"

namespace game_loader {
LoadGame::LoadGame() {}

void LoadGame::Start() {
  int y = 0;
  int x = getmaxx(window_);
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

  int selected_game = SelectGame(y);
  if (selected_game == -1) {
    return;
  }
  SetGame();
  wclear(window_);
  wrefresh(window_);
  player_.SetWindow(window_);
  player_.GameLoop();
  if (player_.IsGameFinished()) {
    Delete(GetGameId());
  }
}

void LoadGame::SetGame() {
  SQLite::Statement query(
      db_, "SELECT GAME_NAME, USER_NAME, LIFE, SECRET_CODE, GUESS_HISTORY, "
           "SCORE, START_TIME, END_TIME, ELAPSED_TIME, HINT_COUNT, "
           "HINT_HISTORY, DIFFICULTY FROM " +
               GetTableName() + " WHERE ID = ?");
  query.bind(1, GetGameId());

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
} // namespace game_loader
