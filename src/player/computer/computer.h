#ifndef COMPUTER_H_
#define COMPUTER_H_

#include "player/player.h"

class ComputerPlayer {
public:
  ComputerPlayer(){};

  void Start();

private:
  Player player;
};

#endif // COMPUTER_H_
