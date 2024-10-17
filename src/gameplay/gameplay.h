#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include "../games/games.h"

#include <chrono>
#include <string>
#include <unordered_map>

class Gameplay {
public:
  Gameplay(){};

  void Start();

  std::string GiveFeedback(const std::string &secret_code,
                           const std::string &guesses);

private:
  const int kLifeStart = 10;
  static std::unordered_map<std::chrono::system_clock::time_point, Games>
      saved_games_;

  void GameMenu();
  void SinglePlayer();
  void ComputerCodebreaker();
  void SaveGame();
  void OverwriteGame(Games game);
  void PlayAgain();
  void CheckGameOver(int &life, const std::string &secret_code);
  std::string InputGuess(const std::string &prompt);
  bool PrintGuesses(std::vector<std::pair<std::string, std::string>> &guesses);
};

#endif // GAMEPLAY_H_
