/**
 * @file player.h
 * @brief Declaration of the Player class
 */

#ifndef PLAYER_PLAYER_H_
#define PLAYER_PLAYER_H_

#include <chrono>
#include <map>
#include <string>
#include <vector>

const int kEasyDifficulty = 1;
const int kMediumDifficulty = 2;
const int kHardDifficulty = 3;

namespace player {
/**
 * @class Player
 * @brief Represents a player in the game.
 *
 * The Player class manages the player's attributes.
 */
class Player {
public:
  /**
   * @brief Default constructor.
   *
   * Initializes the player with default values.
   */
  Player() : life_(kLifeStart), score_(kLifeStart), guess_history_() {}

  /**
   * @brief Parameterized constructor.
   *
   * @param life Initial life value.
   * @param score Initial score value.
   * @param secret_code The secret code the player needs to guess.
   * @param guesses The history of guesses made by the player.
   */
  Player(int &life, int &score, const std::vector<int> &secret_code,
         std::map<std::vector<int>, std::string> &guesses)
      : life_(life), score_(score), secret_code_(secret_code),
        guess_history_(guesses) {}

  /**
   * @brief Virtual destructor.
   */
  virtual ~Player() = default;

  /**
   * @brief Starts the game.
   *
   * This is a pure virtual function that must be implemented by derived
   * classes. Sets up the player and the game, and calls the GameLoop().
   */
  virtual void Start() = 0;

  void DecrementLife();

  void StartTime();
  void EndTime();
  void SaveElapsedTime();

  std::string GetName() const;
  int GetLife() const;
  int GetScore() const;
  int GetSecretCodeMinDigit() const;
  int GetSecretCodeMaxDigit() const;
  int GetSecretCodeLength() const;
  int GetDifficulty() const;
  double GetElapsedTime() const;

  std::vector<int> GetSecretCode() const;

  std::map<std::vector<int>, std::string> GetGuesses() const;

  // SETTERS

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
  std::map<std::vector<int>, std::string> guess_history_;

  /**
   * @brief Main game loop.
   *
   * This is a pure virtual function that must be implemented by derived
   * classes.
   */
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
  std::chrono::time_point<std::chrono::high_resolution_clock> start_time_;
  std::chrono::time_point<std::chrono::high_resolution_clock> end_time_;
  double elapsed_time_;
};

} // namespace player

#endif // PLAYER_PLAYER_H_
