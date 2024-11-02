#ifndef PLAYER_PLAYER_H_
#define PLAYER_PLAYER_H_

#include <map>
#include <string>
#include <vector>

const int kEasyDifficulty = 1;
const int kMediumDifficulty = 2;
const int kHardDifficulty = 3;

namespace player {
class Player {
public:
  Player() : life_(kLifeStart), score_(kLifeStart), guess_history_() {}

  Player(int &life, int &score, const std::vector<int> &secret_code,
         std::map<std::vector<int>, std::string> &guesses)
      : life_(life), score_(score), secret_code_(secret_code),
        guess_history_(guesses) {}

  virtual ~Player() = default;

  virtual void Start() = 0;

  void DecrementLife();

  // getters
  std::string GetName() const;
  int GetLife() const;
  int GetScore() const;
  int GetSecretCodeMinDigit() const;
  int GetSecretCodeMaxDigit() const;
  int GetSecretCodeLength() const;
  int GetDifficulty() const;
  std::vector<int> GetSecretCode() const;
  std::map<std::vector<int>, std::string> GetGuesses() const;

  // setters
  void SetName(const std::string &name);
  void SetLife(const int &life);
  void SetScore(const int &score);
  void SetSecretCodeMinDigit(const int &min_digit);
  void SetSecretCodeMaxDigit(const int &max_digit);
  void SetSecretCodeLength(const int &length);
  void SetSecretCode(const std::vector<int> &secret_code);
  void SetGuesses(std::map<std::vector<int>, std::string> &guesses);
  void SetDifficulty(const int &difficulty);

protected:
  std::string feedback_;
  // TODO: change to std::unordered_map and add hash function
  std::map<std::vector<int>, std::string> guess_history_;

  virtual void GameLoop() = 0;

private:
  static const int kLifeStart = 10;
  int secret_code_min_digit_ = 0;
  int secret_code_max_digit_ = 7;
  int secret_code_length_ = 4;

  std::string name_;
  int life_ = kLifeStart;
  int score_ = 0;
  std::vector<int> secret_code_;
  int difficulty_ = kEasyDifficulty;
  // TODO: add timer
};
} // namespace player

#endif // PLAYER_PLAYER_H_
