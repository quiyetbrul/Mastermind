#ifndef COMPUTER_H_
#define COMPUTER_H_

#include "player/player.h"

namespace player {
class Computer : public Player {
public:
  Computer(){};

  void Start();
};
} // namespace player

#endif // COMPUTER_H_
