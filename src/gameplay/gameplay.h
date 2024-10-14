#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include <string>

class Gameplay {
public:
  Gameplay();

  void Start();

  std::string GiveFeedback(const std::string &secretCode,
                           const std::string &guesses);

private:
  void Game();
  void PlayAgain();
};

#endif // GAMEPLAY_H_
