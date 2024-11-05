/**
 * @file scoreboard.h
 * @brief Declaration of all Scoreboard functions.
 */

#ifndef DATA_MANAGEMENT_SCOREBOARD_SCOREBOARD_H_
#define DATA_MANAGEMENT_SCOREBOARD_SCOREBOARD_H_

#include <set>

#include "logger/logger.h"
#include "player/player.h"
#include "scoreboard_handler.h"

namespace game_data {
/**
 * @class Scoreboard
 * @brief Represents the scoreboard in the game.
 *
 * The Scoreboard class manages the high scores of the game.
 */
class Scoreboard {
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

private:
  data_management::ScoreboardHandler handler_;
  Logger &logger_ = Logger::GetInstance();

  static std::multiset<data_management::ScoreEntry, std::greater<>>
      saved_scores_;
  const int kScoreLimit = 10;

  bool IsHighScore(const int &score) const;
  void AddScore(const player::Player &player);
};
} // namespace game_data

#endif // DATA_MANAGEMENT_SCOREBOARD_SCOREBOARD_H_
