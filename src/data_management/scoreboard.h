/**
 * @file scoreboard.h
 * @brief Declaration of all Scoreboard functions.
 */

#ifndef DATA_MANAGEMENT_SCOREBOARD_H_
#define DATA_MANAGEMENT_SCOREBOARD_H_

#include <SQLiteCpp/SQLiteCpp.h>

#include "database_handler.h"
#include "player/player.h"

namespace data_management {
/**
 * @class Scoreboard
 * @brief Represents the scoreboard in the game.
 *
 * The Scoreboard class manages the high scores of the game.
 */
class Scoreboard : public DatabaseHandler {
public:
  /**
   * @brief Default constructor.
   */
  Scoreboard();

  /**
   * @brief Initializes the scoreboard.
   */
  void Init();

  /**
   * @brief Saves the player's score to the scoreboard.
   *
   * @param player The player whose score needs to be saved.
   */
  void SaveScore(const player::Player &player);

  /**
   * @brief Prints the high scores.
   */
  void PrintScores() const;

  void CreateTable(const std::string &table_name) override;
  void InsertRecord(const std::vector<std::string> &values) override;
  void QueryRecords() override;
  void UpdateRecord(const int &id) override;
  void DeleteRecord(const int &id) override;

private:
  SQLite::Database db_;
};
} // namespace data_management

#endif // DATA_MANAGEMENT_SCOREBOARD_H_
