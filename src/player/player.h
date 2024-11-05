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
  Player();

  /**
   * @brief Parameterized constructor.
   *
   * @param life Initial life value.
   * @param score Initial score value.
   * @param secret_code The secret code the player needs to guess.
   * @param guesses The history of guesses made by the player.
   */
  Player(int &life, int &score, const std::vector<int> &secret_code,
         std::map<std::vector<int>, std::string> &guesses);

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

  /**
   * @brief Decrements the player's life.
   */
  void DecrementLife();

  /**
   * @brief Starts the timer.
   */
  void StartTime();

  /**
   * @brief Ends the timer.
   */
  void EndTime();

  /**
   * @brief Saves the elapsed time.
   */
  void SaveElapsedTime();

  // GETTERS

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
  std::string last_feedback_;
  std::map<std::vector<int>, std::string> guess_history_;
  static constexpr int kEasyDifficulty = 1;
  static constexpr int kMediumDifficulty = 2;
  static constexpr int kHardDifficulty = 3;

  /**
   * @brief Main game loop.
   *
   * This is a pure virtual function that must be implemented by derived
   * classes.
   */
  virtual void GameLoop() = 0;

  /**
   * @brief Adds a guess to the history.

  * This checks whether the guess already exists in the history. If it does, it
  * does not add it. Otherwise, it adds the guess to the history and updates
  * last_feedback_.
   *
   * @param guess The guess to add.
   */
  void AddToGuessHistory(const std::vector<int> &guess);

private:
  static constexpr int kLifeStart = 10;
  int secret_code_min_digit_;
  int secret_code_max_digit_;
  int secret_code_length_;

  std::string name_;
  int life_ = kLifeStart;
  int score_ = 0;
  std::vector<int> secret_code_;
  int difficulty_ = kEasyDifficulty;
  std::chrono::time_point<std::chrono::high_resolution_clock> start_time_;
  std::chrono::time_point<std::chrono::high_resolution_clock> end_time_;
  double elapsed_time_;

  /**
   * @brief Initializes the player.
   *
   * Sets the secret code attribute.
   */
  void Init();
};
} // namespace player

#endif // PLAYER_PLAYER_H_
