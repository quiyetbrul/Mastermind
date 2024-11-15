/**
 * @file score.h
 * @brief Declaration of all Score functions.
 */

#ifndef DATA_MANAGEMENT_SCOREBOARD_SCORE_H_
#define DATA_MANAGEMENT_SCOREBOARD_SCORE_H_

#include "data_management/scoreboard/scoreboard.h"
#include "player/player.h"
#include <ncurses.h>

namespace data_management {
/**
 * @class Score
 * @brief Represents the scoreboard in the game.
 *
 * The Score class is a high level high score manager.
 */
class Score : public data_management::Scoreboard {
public:
  /**
   * @brief Default constructor.
   */
  Score();

  /**
   * @brief Saves the player's score to the scoreboard.
   *
   * @param player The player whose score needs to be saved.
   */
  void Save(const player::Player &player);

  /**
   * @brief Prints the high scores.
   */
  void PrintScores(WINDOW *window) const;
};
} // namespace data_management

#endif // DATA_MANAGEMENT_SCOREBOARD_SCORE_H_
