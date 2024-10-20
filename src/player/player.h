#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include <utility>
#include <vector>

class Player {
public:
  static const int kLifeStart = 10;

  Player() {
    life_ = kLifeStart;
    score_ = kLifeStart;
  };

  Player(int &life, int &score, const std::vector<int> &secret_code,
         std::vector<std::pair<std::vector<int>, std::string>> &guesses)
      : life_(life), score_(score), secret_code_(secret_code),
        guesses_(guesses){};

  void DecrementLife();
  void DecrementScore();
  void AddGuess(const std::vector<int> &guess, const std::string &feedback);

  // getters
  int GetLife() const;
  int GetScore() const;
  std::vector<int> GetSecretCode() const;
  std::vector<std::pair<std::vector<int>, std::string>> GetGuesses() const;

  // setters
  void SetLife(const int &life);
  void SetScore(const int &score);
  void SetSecretCode(const std::vector<int> &secret_code);
  void
  SetGuesses(std::vector<std::pair<std::vector<int>, std::string>> &guesses);

private:
  int life_ = kLifeStart;
  int score_ = 0;
  std::vector<int> secret_code_;
  std::vector<std::pair<std::vector<int>, std::string>> guesses_;
};

#endif // PLAYER_H_
