#ifndef SINGLE_SINGLE_H_
#define SINGLE_SINGLE_H_

#include "player/player.h"

namespace player {
class Single : public Player {
public:
  Single(){};

  void Start() override;

protected:
  void GameLoop() override;
};
} // namespace player

#endif // SINGLE_SINGLE_H_
