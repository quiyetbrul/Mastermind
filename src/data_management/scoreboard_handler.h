#ifndef DATA_MANAGEMENT_SCOREBOARD_HANDLER_HANDLER_H_
#define DATA_MANAGEMENT_SCOREBOARD_HANDLER_HANDLER_H_

#include <set>
#include <string>

struct ScoreEntry {
  int score;
  std::string name;
  int difficulty;

  ScoreEntry(int s, const std::string &n, const int &d)
      : score(s), name(n), difficulty(d) {}

  bool operator>(const ScoreEntry &other) const { return score > other.score; }
};

class ScoreboardHandler {
public:
  ScoreboardHandler(){Init();};

  ScoreboardHandler(const std::string &file_name) : file_name_(file_name) {
    Init();
  }

  std::multiset<ScoreEntry, std::greater<>> GetSavedScores();

  void UpdateScoreboard(
      const std::multiset<ScoreEntry, std::greater<>> &saved_scores);

  std::string HeaderToString(const std::string &delim) const;

private:
  void Init();
  std::string file_name_;
  static std::vector<std::string> header_;
};

#endif // DATA_MANAGEMENT_SCOREBOARD_HANDLER_HANDLER_H_
