#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include <vector>

class Gameplay {
public:
  Gameplay();

  void Start();
  std::string GiveFeedback(const std::vector<int> &secretCode,
                    const std::vector<int> &userGuess);

private:
  void Game();
  void PlayAgain();
};

#endif // GAMEPLAY_H_
