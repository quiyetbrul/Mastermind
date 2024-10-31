#ifndef GAME_DATA_SCOREBOARD_SCOREBOARD_H_
#define GAME_DATA_SCOREBOARD_SCOREBOARD_H_

#include <string>
#include <utility>
#include <vector>

#include "data_management/scoreboard_handler.h"
#include "player/player.h"

namespace game_data {
class Scoreboard {
public:
  static Scoreboard &GetInstance() {
    static Scoreboard instance;
    return instance;
  }

  void SaveScore(const player::Player &player);

  void PrintScores() const;

private:
  Scoreboard();
  // TODO: make deleted functions public per Effective Modern C++
  Scoreboard(const Scoreboard &) = delete;
  Scoreboard &operator=(const Scoreboard &) = delete;

  ScoreboardHandler handler_;

  static std::vector<std::pair<std::string, int>> saved_scores_;
  const int kScoreLimit = 10;

  bool IsHighScore(const int &score) const;
  void AddScore(const std::string &name, const int &score);
};
} // namespace game_data

#endif // GAME_DATA_SCOREBOARD_SCOREBOARD_H_
