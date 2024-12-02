/**
 * @file codebreaker.h
 * @brief Declaration of the Codebreaker class.
 */

#ifndef PLAYER_PLAYER_TYPE_CODEMASTER_CODEBREAKER_H_
#define PLAYER_PLAYER_TYPE_CODEMASTER_CODEBREAKER_H_

#include <map>
#include <set>
#include <string>
#include <vector>

namespace player {
/**
 * @class Codebreaker
 * @brief Represents the computer player that breaks the code.
 *
 * The Codebreaker class manages the computer player's attributes.
 * The Codebreaker class is responsible for generating guesses and filtering
 * the possible solutions based on the feedback received from the Codemaker.
 * The Codebreaker is based on Donald Knuth's Five-guess algorithm.
 *
 * In the game of Mastermind, the minimax algorithm can be used by the
 * codebreaker to determine the next guess. Here's how it works:
 *
 * 1. Generate Possible Guesses: The algorithm generates all possible guesses
 * that the codebreaker can make.
 *
 * 2. Simulate Feedback: For each possible guess, the algorithm
 * simulates the feedback that would be received if that guess were made.
 *
 * 3. Evaluate Worst-Case Scenarios: For each possible guess, the algorithm
 * considers the worst-case scenario, which is the feedback that would leave the
 * most possible codes remaining.
 *
 * 4. Select Optimal Guess: The algorithm selects the guess that minimizes the
 * maximum number of remaining possible codes, effectively reducing the search
 * space and increasing the chances of cracking the code in fewer attempts.
 */
class Codebreaker {
public:
  /**
   * @brief Constructor for the Codebreaker class.
   *
   * This constructor initializes the Codebreaker object with the specified
   * code length, minimum digit, and maximum digit.
   *
   * @param code_length The length of the code.
   * @param min_digit The minimum digit of the code.
   * @param max_digit The maximum digit of the code.
   */
  Codebreaker(int code_length, int min_digit, int max_digit);

  /**
   * @brief Generate the next guess.
   *
   * This function generates the next guess based on the minimax algorithm.
   *
   * @return std::vector<int> The next guess.
   */
  std::vector<int> MakeGuess();

  /**
   * @brief Remove the code from the set.
   *
   * This function removes the code from the set of all possible combinations
   * and all possible solutions.
   *
   * @param guess The guess to remove.
   */
  void RemoveCode(const std::vector<int> &guess);

  /**
   * @brief Filter the solutions based on the feedback.
   *
   * The function aims to remove all candidate solutions from
   * candidate_solutions_ that do not produce the same feedback when compared to
   * the given guess.
   *
   * @param guess The guess made by the Codebreaker.
   * @param feedback The feedback received from the Codemaker.
   */
  void FilterSolutions(const std::vector<int> &guess,
                       const std::string &feedback);

private:
  const int code_length_;
  const int min_digit_;
  const int max_digit_;

  std::set<std::vector<int>> combinations_;
  std::set<std::vector<int>> candidate_solutions_;

  /**
   * @brief Create a Set object
   *
   * This function creates a set of all possible combinations and all possible
   * solutions of the code.
   */
  void Init();

  /**
   * @brief Helper to CreateSet().
   *
   * Generates all possible combinations of the code.
   *
   */
  void GenerateCombinations();

  /**
   * @brief Helper to RemoveCode(const std::vector<int> &).
   *
   * This function removes the code from the set.
   *
   * @param set The set to remove the code from.
   * @param guess The guess to remove.
   */
  void RemoveCode(std::set<std::vector<int>> &set,
                  const std::vector<int> &guess);

  /**
   * @brief Minimax algorithm to find the next guess.
   *
   * The minimax algorithm is a decision-making algorithm used in game theory
   * and artificial intelligence to find the optimal move for a player by
   * minimizing the possible loss for a worst-case scenario. It works by
   * evaluating the possible moves, assuming that the opponent will
   * also play optimally, and selecting the move that maximizes the player's
   * minimum gain.
   *
   * @return std::vector<std::vector<int>>
   */
  std::vector<std::vector<int>> Minimax();

  /**
   * @brief Get the maximum score from the score count.
   *
   * Represents the maximum score for a given guess. This score is determined by
   * evaluating the worst-case scenario for each possible guess, which is the
   * feedback that would leave the most possible codes remaining. Essentially,
   * max is used to track the highest number of remaining possibilities for each
   * guess.
   *
   * @param score_count The score count.
   * @return int The maximum score.
   */
  int GetMaxScore(const std::map<std::string, int> &score_count);

  /**
   * @brief Get the minimum score from the score.
   *
   * Represents the minimum value among the maximum scores of all possible
   * guesses. After calculating the max score for each guess, min is used to
   * find the guess that has the smallest worst-case scenario. This means
   * selecting the guess that minimizes the maximum number of remaining
   * possibilities, effectively reducing the search space and improving the
   * chances of solving the code efficiently.
   *
   * @param score The score.
   * @return int The minimum score.
   */
  int GetMinScore(const std::map<std::vector<int>, int> &score);
};
} // namespace player

#endif // PLAYER_PLAYER_TYPE_CODEMASTER_CODEBREAKER_H_
