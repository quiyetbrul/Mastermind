#ifndef DATA_MANAGEMENT_SCOREBOARD_SCOREBOARD_H_
#define DATA_MANAGEMENT_SCOREBOARD_SCOREBOARD_H_

#include <set>

#include "player/player.h"
#include "scoreboard_handler.h"

namespace game_data {
class Scoreboard {
public:
  Scoreboard();

  void Init();

  void SaveScore(const player::Player &player);

  void PrintScores() const;

private:
  data_management::ScoreboardHandler handler_;

  static std::multiset<data_management::ScoreEntry, std::greater<>>
      saved_scores_;
  const int kScoreLimit = 10;

  bool IsHighScore(const int &score) const;
  void AddScore(const player::Player &player);
};
} // namespace game_data

#endif // DATA_MANAGEMENT_SCOREBOARD_SCOREBOARD_H_
