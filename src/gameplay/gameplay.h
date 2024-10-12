#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include <vector>

class Gameplay {
public:
  Gameplay();

  void Start();

private:
  void Game();
  void GiveFeedback(const std::vector<int> &secretCode,
                    const std::vector<int> &userGuess);
  void PlayAgain();
};

#endif // GAMEPLAY_H_
