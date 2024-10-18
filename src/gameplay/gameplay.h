#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include <string>
#include <vector>

#include "../games/games.h"

class Gameplay {
public:
  Gameplay(){};

  void Start();

  std::string GiveFeedback(const std::string &secret_code,
                           const std::string &guesses);

private:
  const int kLifeStart = 10;
  const int save_limit_ = 3;
  static std::vector<Games> saved_games_;

  void GameMenu();
  void SinglePlayer();
  void ComputerCodebreaker();
  void SaveGame(const Player &player);
  void OverwriteGame(const Games &game);
  void PlayAgain();
  void CheckGameOver(int &life, const std::string &secret_code);
  std::string InputGuess(const std::string &prompt);
  void
  PrintGuesses(const std::vector<std::pair<std::string, std::string>> &guesses);
};

#endif // GAMEPLAY_H_
