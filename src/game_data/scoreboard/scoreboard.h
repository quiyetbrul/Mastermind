#ifndef GAME_DATA_SCOREBOARD_SCOREBOARD_H_
#define GAME_DATA_SCOREBOARD_SCOREBOARD_H_

#include <set>

#include "data_management/scoreboard_handler.h"
#include "player/player.h"

namespace game_data {
class Scoreboard {
public:
  Scoreboard();

  void Init();

  void SaveScore(const player::Player &player);

  void PrintScores() const;

private:
  ScoreboardHandler handler_;

  static std::multiset<ScoreEntry, std::greater<>> saved_scores_;
  const int kScoreLimit = 10;

  bool IsHighScore(const int &score) const;
  void AddScore(const player::Player& player);
};
} // namespace game_data

#endif // GAME_DATA_SCOREBOARD_SCOREBOARD_H_
