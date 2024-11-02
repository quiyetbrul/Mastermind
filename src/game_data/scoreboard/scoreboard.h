#ifndef GAME_DATA_SCOREBOARD_SCOREBOARD_H_
#define GAME_DATA_SCOREBOARD_SCOREBOARD_H_

#include <set>
#include <string>
#include <utility>

#include "data_management/scoreboard_handler.h"
#include "player/player.h"

namespace game_data {
class Scoreboard {
public:
  static Scoreboard &GetInstance() {
    static Scoreboard instance;
    return instance;
  }

  Scoreboard(const Scoreboard &) = delete;
  Scoreboard &operator=(const Scoreboard &) = delete;

  void SaveScore(const player::Player &player);

  void PrintScores() const;

private:
  Scoreboard();

  ScoreboardHandler handler_;

  static std::multiset<std::pair<int, std::string>, std::greater<>>
      saved_scores_;
  const int kScoreLimit = 10;

  bool IsHighScore(const int &score) const;
  void AddScore(const int &score, const std::string &name);
};
} // namespace game_data

#endif // GAME_DATA_SCOREBOARD_SCOREBOARD_H_
