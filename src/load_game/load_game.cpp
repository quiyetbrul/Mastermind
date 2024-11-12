/**
 * @file load_game.cpp
 * @brief Implementation of all LoadGame functions.
 */

#include "load_game.h"

namespace game_loader {
LoadGame::LoadGame() {}

void LoadGame::SelectedGame(const int &game_id) {
  SetGameId(game_id);

  // Open the database
  SQLite::Database db(MASTERMIND_DB_PATH, SQLite::OPEN_READWRITE);

  // Prepare the SQL query
  SQLite::Statement query(
      db, "SELECT GAME_NAME, USER_NAME, LIFE, SECRET_CODE, GUESS_HISTORY, "
          "SCORE, START_TIME, END_TIME, ELAPSED_TIME, HINT_COUNT, "
          "HINT_HISTORY, DIFFICULTY FROM " +
              game_.GetTableName() + " WHERE ID = ?");
  query.bind(1, game_id);

  if (query.executeStep()) {
    // Get the player's game from the database.
    player_.SetGameName(query.getColumn(0).getText());
    player_.SetPlayerName(query.getColumn(1).getText());
    player_.SetLife(query.getColumn(2).getInt());
    player_.SetSecretCode(ConvertToArray<int>(query.getColumn(3).getText()));
    player_.SetGuesses(
        game_.ConvertToArray<std::pair<std::vector<int>, std::string>>(
            query.getColumn(4).getText()));
    player_.SetScore(query.getColumn(5).getInt());
    player_.SetStartTime(query.getColumn(6).getDouble());
    player_.SetEndTime(query.getColumn(7).getDouble());
    player_.SetElapsedTime(query.getColumn(8).getDouble());
    player_.SetHintCount(query.getColumn(9).getInt());
    player_.SetHintHistory(
        game_.ConvertToArray<std::string>(query.getColumn(10).getText()));
    player_.SetDifficulty(query.getColumn(11).getInt());
  } else {
    // Handle the case where the game to load was not found
    throw std::runtime_error("Game to load not found");
  }
}

void LoadGame::Start() {
  player_.GameLoop();
  if (player_.IsGameFinished()) {
    Delete(GetGameId());
  }
}

int LoadGame::GetGameId() { return game_id_; }

void LoadGame::SetGameId(const int &game_id) { game_id_ = game_id; }

} // namespace game_loader
