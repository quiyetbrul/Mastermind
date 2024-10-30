#ifndef PLAYER_PLAYER_H_
#define PLAYER_PLAYER_H_

#include <map>
#include <string>
#include <vector>

#include "player/computer/codebreaker/codebreaker.h"

namespace player {
class Player {
public:
  Player() : life_(kLifeStart), score_(kLifeStart), guess_history_() {}

  Player(int &life, int &score, const std::vector<int> &secret_code,
         std::map<std::vector<int>, std::string> &guesses)
      : life_(life), score_(score), secret_code_(secret_code),
        guess_history_(guesses) {}

  void DecrementLife();
  void AddGuess(const std::vector<int> &guess, const std::string &feedback);

  // getters
  std::string GetName() const;
  int GetLife() const;
  int GetScore() const;
  std::vector<int> GetSecretCode() const;
  std::map<std::vector<int>, std::string> GetGuesses() const;

  // setters
  void SetName(const std::string &name);
  void SetLife(const int &life);
  void SetScore(const int &score);
  void SetSecretCode(const std::vector<int> &secret_code);
  void SetGuesses(std::map<std::vector<int>, std::string> &guesses);

protected:
  void GameLoop(Codebreaker *computer = nullptr,
                std::vector<int> initial_guess = {});

private:
  static const int kLifeStart = 10;
  std::string name_;
  int life_ = kLifeStart;
  int score_ = 0;
  std::vector<int> secret_code_;
  std::string feedback_;
  // TODO: change to std::unordered_map and add hash function
  std::map<std::vector<int>, std::string> guess_history_;
};
} // namespace player

#endif // PLAYER_PLAYER_H_
