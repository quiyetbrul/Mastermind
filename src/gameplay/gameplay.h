#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include <string>

class Gameplay {
public:
  Gameplay();

  void Start();

  std::string GiveFeedback(const std::string &secret_code,
                           const std::string &guesses);

private:
  // TODO: saved games
  // std::unordered_map</*name+password*/std::string, Games games> saved_games_;

  void GameMenu();
  void SinglePlayer();
  void ComputerCodebreaker();
  void PlayAgain();

  // TODO: print how many guesses guesser took

  std::string InputGuess(const std::string &prompt);
  std::string InputString(const std::string &prompt);
  bool PrintGuesses(std::vector<std::pair<std::string, std::string>> &guesses);
};

#endif // GAMEPLAY_H_
