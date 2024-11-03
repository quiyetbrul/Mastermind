#ifndef GAME_DATA_SCOREBOARD_SCOREBOARD_H_
#define GAME_DATA_SCOREBOARD_SCOREBOARD_H_

#include <memory>
#include <mutex>
#include <set>

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

  void Init();

  void SaveScore(const player::Player &player);

  void PrintScores() const;

private:
  Scoreboard();

  ScoreboardHandler handler_;

  static std::multiset<ScoreEntry, std::greater<>> saved_scores_;
  const int kScoreLimit = 10;

  bool IsHighScore(const int &score) const;
  void AddScore(const player::Player& player);
};
} // namespace game_data

#endif // GAME_DATA_SCOREBOARD_SCOREBOARD_H_
