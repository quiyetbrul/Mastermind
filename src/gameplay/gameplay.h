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

  void Game();
  void SinglePlayer();
  void MultiPlayer();
  void AgainstComputer();
  void PlayAgain();

  // TODO: print how many guesses guesser took

  std::string InputGuess(const std::string &prompt);
  std::string InputString(const std::string &prompt);
  void CheckGuess(const std::string &user_guess, const std::string &secret_code,
                  std::vector<std::pair<std::string, std::string>> &guesses,
                  int &life);
};

#endif // GAMEPLAY_H_
