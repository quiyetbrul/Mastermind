#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include <vector>

#include "games/games.h"

class Gameplay {
public:
  Gameplay(){};

  void Start();

private:
  static const int kLifeStart = 10;
  static const int save_limit_ = 3;
  static std::vector<Games> saved_games_;

  void GameMenu();
  void PlayAgain();
};

#endif // GAMEPLAY_H_
