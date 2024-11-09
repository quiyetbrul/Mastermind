/**
 * @file scoreboard.h
 * @brief Declaration of all Scoreboard functions.
 */

#ifndef DATA_MANAGEMENT_SCOREBOARD_H_
#define DATA_MANAGEMENT_SCOREBOARD_H_

#include <SQLiteCpp/SQLiteCpp.h>

#include "database_manager.h"
#include "player/player.h"

namespace data_management {
/**
 * @class Scoreboard
 * @brief Represents the scoreboard in the game.
 *
 * The Scoreboard class manages the high scores of the game.
 */
class Scoreboard : public DatabaseManager {
public:
  /**
   * @brief Default constructor.
   */
  Scoreboard();

  /**
   * @brief Saves the player's score to the scoreboard.
   *
   * @param player The player whose score needs to be saved.
   */
  void Save(const player::Player &player);

  /**
   * @brief Prints the high scores.
   */
  void PrintScores() const;

protected:
  void CreateTable(const std::string &table_name) override;

private:
  SQLite::Database db_;

  /**
   * @brief Gets the number of records in the scoreboard.
   *
   * @return The number of records in the scoreboard.
   */
  int GetCount() const;

  /**
   * @brief Gets the lowest score in the scoreboard.
   *
   * @return The lowest score in the scoreboard.
   */
  SQLite::Statement GetLowestScore() const;

  /**
   * @brief Inserts a player into the scoreboard.
   *
   * @param player The player to be inserted.
   */
  void Insert(const player::Player &player);

  /**
   * @brief Updates the scoreboard with the player's score.
   *
   * @param lowest_score The lowest score in the scoreboard.
   * @param player The player whose score needs to be updated.
   */
  void Update(const SQLite::Statement &lowest_score,
              const player::Player &player);
};
} // namespace data_management

#endif // DATA_MANAGEMENT_SCOREBOARD_H_
