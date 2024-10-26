#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include <utility>
#include <vector>

// TODO: single_player and multiplayer should inherit from Player
// Player Factory Method Pattern
class Player {
public:
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
  std::string GetName() const;
  int GetLife() const;
  int GetScore() const;
  std::vector<int> GetSecretCode() const;
  std::vector<std::pair<std::vector<int>, std::string>> GetGuesses() const;
  bool IsWinner() const;

  // setters
  void SetName(const std::string &name);
  void SetLife(const int &life);
  void SetScore(const int &score);
  void SetSecretCode(const std::vector<int> &secret_code);
  void SetGuesses(std::vector<std::pair<std::vector<int>, std::string>> &guesses);
  void SetWinner(const bool &is_winner);

private:
  static const int kLifeStart = 10;
  std::string name_;
  int life_ = kLifeStart;
  int score_ = 0;
  bool is_winner_ = false;
  std::vector<int> secret_code_;

  // TODO: Change to std::map
  std::vector<std::pair<std::vector<int>, std::string>> guesses_;
};

#endif // PLAYER_H_
