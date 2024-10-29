#ifndef PLAYER_COMPUTER_H_
#define PLAYER_COMPUTER_H_

#include "player/player.h"

namespace player {
class Computer : public Player {
public:
  Computer(){};

  void Start();
};
} // namespace player

#endif // PLAYER_COMPUTER_H_
