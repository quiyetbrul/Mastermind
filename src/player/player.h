/**
 * @file player.h
 * @brief Declaration of the Player class
 */

#ifndef PLAYER_PLAYER_H_
#define PLAYER_PLAYER_H_

#include <chrono>
#include <string>
#include <utility>
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
         std::vector<std::pair<std::vector<int>, std::string>> &guesses);

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
   * @brief Main game loop.
   *
   * This is a pure virtual function that must be implemented by derived
   * classes.
   */
  virtual void GameLoop() = 0;

  // GETTERS

  std::string GetPlayerName() const;
  std::string GetGameName() const;
  int GetLife() const;
  int GetScore() const;
  int GetSecretCodeMinDigit() const;
  int GetSecretCodeMaxDigit() const;
  int GetSecretCodeLength() const;
  int GetDifficulty() const;
  double GetStartTime() const;
  double GetEndTime() const;
  double GetElapsedTime() const;
  std::vector<int> GetSecretCode() const;
  std::vector<std::pair<std::vector<int>, std::string>> GetGuesses() const;
  int GetHintCount() const;
  std::vector<std::string> GetHintHistory() const;
  std::string GetLastFeedBack() const;

  // SETTERS

  void SetPlayerName(const std::string &name);
  void SetGameName(const std::string &name);
  void SetLife(const int &life);
  void SetScore(const int &score);
  void SetSecretCodeMinDigit(const int &min_digit);
  void SetSecretCodeMaxDigit(const int &max_digit);
  void SetSecretCodeLength(const int &length);
  void SetSecretCode(const std::vector<int> &secret_code);
  void SetGuesses(
      const std::vector<std::pair<std::vector<int>, std::string>> &guesses);
  void SetDifficulty(const int &difficulty);
  void SetHintCount(const int &hint_count);
  void SetHintHistory(const std::vector<std::string> &hint_history);
  void SetLastFeedBack(const std::string &feedback);

protected:
  static constexpr int kEasyDifficulty = 1;
  static constexpr int kMediumDifficulty = 2;
  static constexpr int kHardDifficulty = 3;

  /**
   * @brief Decrements the player's life.
   */
  void DecrementLife();

  /**
   * @brief Decrements the player's hint count.
   */
  void DecrementHint();

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

  /**
   * @brief Add hint to hint_history_
   *
   */
  void AddToHintHistory(const std::string &hint);

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
  int difficulty_ = kEasyDifficulty;
  int secret_code_min_digit_;
  int secret_code_max_digit_;
  int secret_code_length_;

  std::string player_name_;
  std::string game_name_;
  int life_;
  int score_ = 0;
  std::vector<int> secret_code_;

  std::string last_feedback_;
  std::vector<std::pair<std::vector<int>, std::string>> guess_history_;

  std::chrono::time_point<std::chrono::high_resolution_clock> start_time_;
  std::chrono::time_point<std::chrono::high_resolution_clock> end_time_;
  double elapsed_time_;

  int hint_count_ = 3;
  std::vector<std::string> hint_history_;
};
} // namespace player

#endif // PLAYER_PLAYER_H_
