#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include <string>
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
  void SinglePlayer();
  void ComputerCodebreaker();
  void PlayAgain();
  void CheckGameOver(int &life, const std::string &secret_code);
  std::vector<int> InputGuess(const std::string &prompt);
  void PrintGuesses(
      const std::vector<std::pair<std::vector<int>, std::string>> &guesses);
};

#endif // GAMEPLAY_H_
