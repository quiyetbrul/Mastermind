#ifndef GAMESTATE_GAMESTATE_H_
#define GAMESTATE_GAMESTATE_H_

namespace mastermind {
class GameState {
public:
  GameState(){};

  void Start();

private:
  void Menu();
  void PlayAgain();
};
} // namespace mastermind

#endif // GAMESTATE_GAMESTATE_H_
