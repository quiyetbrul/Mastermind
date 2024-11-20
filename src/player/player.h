/**
 * @file player.h
 * @brief Abstract class declaration of the Player class
 */

#ifndef PLAYER_PLAYER_H_
#define PLAYER_PLAYER_H_

#include <chrono>
#include <string>
#include <utility>
#include <vector>

#include "logger/logger.h"

#include <ncurses.h>

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

  /**
   * @brief Checks if the game is finished.
   *
   * @return true If the game is finished.
   * @return false If the game is not finished.
   */
  bool IsGameFinished() const;

  // GETTERS

  std::string GetPlayerName() const { return player_name_; }
  std::string GetGameName() const { return game_name_; }
  int GetGameId() const { return game_id_; }
  int GetLife() const { return life_; }
  int GetScore() const { return score_; }
  int GetSecretCodeMinDigit() const { return secret_code_min_digit_; }
  int GetSecretCodeMaxDigit() const { return secret_code_max_digit_; }
  int GetSecretCodeLength() const { return secret_code_length_; }
  int GetDifficulty() const { return difficulty_; }
  double GetStartTime() const { return start_time_.time_since_epoch().count(); }
  double GetEndTime() const { return end_time_.time_since_epoch().count(); }
  double GetElapsedTime() const { return elapsed_time_; }
  std::vector<int> GetSecretCode() const { return secret_code_; }
  std::vector<std::pair<std::vector<int>, std::string>> GetGuesses() const {
    return guess_history_;
  }
  int GetHintCount() const { return hint_count_; }
  std::vector<std::string> GetHintHistory() const { return hint_history_; }
  std::string GetLastFeedBack() const { return last_feedback_; }

  // SETTERS

  void SetWindow(WINDOW *window) { window_ = window; }
  void SetPlayerName(const std::string &name) { player_name_ = name; }
  void SetGameName(const std::string &name) { game_name_ = name; }
  void SetGameId(const int &id) { game_id_ = id; }
  void SetLife(const int &life) { life_ = life; }
  void SetScore(const int &score) { score_ = score; }
  void SetStartTime(const double &start_time) {
    start_time_ = std::chrono::time_point<std::chrono::high_resolution_clock>(
        std::chrono::nanoseconds(static_cast<long long>(start_time)));
  }
  void SetEndTime(const double &end_time) {
    end_time_ = std::chrono::time_point<std::chrono::high_resolution_clock>(
        std::chrono::nanoseconds(static_cast<long long>(end_time)));
  }
  void SetElapsedTime(const double &elapsed_time) {
    elapsed_time_ = elapsed_time;
  }
  void SetSecretCodeMinDigit(const int &min_digit) {
    secret_code_min_digit_ = min_digit;
  }
  void SetSecretCodeMaxDigit(const int &max_digit) {
    secret_code_max_digit_ = max_digit;
  }
  void SetSecretCodeLength(const int &length) { secret_code_length_ = length; }
  void SetSecretCode(const std::vector<int> &secret_code) {
    secret_code_ = secret_code;
  }
  void SetGuesses(
      const std::vector<std::pair<std::vector<int>, std::string>> &guesses) {
    guess_history_ = guesses;
  }
  void SetDifficulty(const int &difficulty) {
    switch (difficulty) {
    case 1: // Easy
      SetSecretCodeMinDigit(kEasyMinDigit);
      SetSecretCodeMaxDigit(kEasyMaxDigit);
      SetSecretCodeLength(kEasyCodeLength);
      break;
    case 2: // Medium
      SetSecretCodeMinDigit(kMediumMinDigit);
      SetSecretCodeMaxDigit(kMediumMaxDigit);
      SetSecretCodeLength(kMediumCodeLength);
      break;
    case 3: // Hard
      SetSecretCodeMinDigit(kHardMinDigit);
      SetSecretCodeMaxDigit(kHardMaxDigit);
      SetSecretCodeLength(kHardCodeLength);
      break;
    }
    logger_.Log("Difficulty set to " + std::to_string(difficulty));
    difficulty_ = difficulty;
  }
  void SetHintCount(const int &hint_count) { hint_count_ = hint_count; }
  void SetHintHistory(const std::vector<std::string> &hint_history) {
    hint_history_ = hint_history;
  }
  void SetLastFeedBack(const std::string &feedback) {
    last_feedback_ = feedback;
  }

protected:
  Logger &logger_ = Logger::GetInstance();
  WINDOW *window_;

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
   *
   * This checks whether the guess already exists in the history. If it does,it
   * does not add it. Otherwise, it adds the guess to the history and updates
   * last_feedback_.
   *
   * @param guess The guess to add.
   */
  void AddToGuessHistory(const std::vector<int> &guess);

private:
  const int kLifeStart = 10;

  const int kEasyMinDigit = 0;
  const int kEasyMaxDigit = 7;
  const int kEasyCodeLength = 4;

  const int kMediumMinDigit = 0;
  const int kMediumMaxDigit = 8;
  const int kMediumCodeLength = 4;

  const int kHardMinDigit = 0;
  const int kHardMaxDigit = 9;
  const int kHardCodeLength = 4;

  int difficulty_ = 1; // Default difficulty is easy
  int secret_code_min_digit_;
  int secret_code_max_digit_;
  int secret_code_length_;

  std::string player_name_;
  std::string game_name_;
  int game_id_;
  int life_;
  int score_;
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
