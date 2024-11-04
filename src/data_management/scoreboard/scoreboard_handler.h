#ifndef DATA_MANAGEMENT_SCOREBOARD_HANDLER_HANDLER_H_
#define DATA_MANAGEMENT_SCOREBOARD_HANDLER_HANDLER_H_

#include <set>
#include <string>
#include <vector>

namespace data_management {
/**
 * @struct ScoreEntry
 * @brief Represents a single entry in the scoreboard.
 *
 * The ScoreEntry struct contains the score, name, elapsed time, and difficulty
 * of a player's game.
 */
struct ScoreEntry {
  int score;
  std::string name;
  double elapsed_time;
  int difficulty;

  /**
   * @brief Constructs a ScoreEntry.
   * @param s The score of the player.
   * @param n The name of the player.
   * @param t The elapsed time of the game.
   * @param d The difficulty level of the game.
   */
  ScoreEntry(int s, const std::string &n, const double &t, const int &d)
      : score(s), name(n), elapsed_time(t), difficulty(d) {}

  /**
   * @brief Comparison operator for sorting ScoreEntry objects.
   * @param other The other ScoreEntry to compare against.
   * @return True if this ScoreEntry has a greater score than the other.
   */
  bool operator>(const ScoreEntry &other) const { return score > other.score; }
};

/**
 * @class ScoreboardHandler
 * @brief Handles the scoreboard data.
 *
 * The ScoreboardHandler class manages the scoreboard data. It reads the saved
 * scores from a file, updates the scoreboard with new scores, and writes the
 * updated scoreboard back to the file.
 */
class ScoreboardHandler {
public:
  /**
   * @brief Default constructor.
   */
  ScoreboardHandler() { Init(); };

  /**
   * @brief Parameterized constructor.
   * @param file_name The name of the file to read and write the scoreboard
   * data.
   */
  ScoreboardHandler(const std::string &file_name) : file_name_(file_name) {
    Init();
  }

  /**
   * @brief Gets the saved scores from the file.
   * @return A multiset of ScoreEntry objects sorted by score in descending
   * order.
   */
  std::multiset<ScoreEntry, std::greater<>> GetSavedScores();

  /**
   * @brief Updates the scoreboard with new scores.
   *
   * @param saved_scores The new scores to add to the scoreboard.
   */
  void UpdateScoreboard(
      const std::multiset<ScoreEntry, std::greater<>> &saved_scores);

  /**
   * @brief Converts the header to a string.
   * @param delim The delimiter to use between header elements.
   * @return The header as a string.
   */
  std::string HeaderToString(const std::string &delim) const;

private:
  std::string file_name_;
  std::vector<std::string> header_;

  /**
   * @brief Initializes the ScoreboardHandler.
   */
  void Init();
};
} // namespace data_management
#endif // DATA_MANAGEMENT_SCOREBOARD_HANDLER_HANDLER_H_
