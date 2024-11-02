#ifndef DATA_MANAGEMENT_SCOREBOARD_HANDLER_HANDLER_H_
#define DATA_MANAGEMENT_SCOREBOARD_HANDLER_HANDLER_H_

#include <set>
#include <string>

class ScoreboardHandler {
public:
  ScoreboardHandler(){};

  ScoreboardHandler(const std::string &file_name) : file_name_(file_name) {}

  std::multiset<std::pair<int, std::string>, std::greater<>>
  GetSavedScores() const;

  void UpdateScoreboard(const std::multiset<std::pair<int, std::string>,
                                            std::greater<>> &saved_scores);

private:
  std::string file_name_;
};

#endif // DATA_MANAGEMENT_SCOREBOARD_HANDLER_HANDLER_H_
