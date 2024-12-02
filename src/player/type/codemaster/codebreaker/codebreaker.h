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
   * @brief Helper to CreateSet().
   *
   * Generates all possible combinations of the code.
   *
   */
  void GenerateCombinations();

  /**
   * @brief Minimax algorithm to find the next guess.
   *
   * The Minimax algorithm is used to find the optimal next guess in a
   * code-breaking game, such as Mastermind. It works by evaluating all possible
   * guesses to minimize the worst-case number of remaining candidate solutions
   * after the guess. The algorithm assumes a strategy that seeks to minimize
   * the worst-case scenario, effectively reducing the search space and
   * improving the efficiency of finding the solution.
   *
   * For each possible guess:
   * - Simulate feedback for the guess against all remaining candidate
   * solutions.
   * - Calculate the size of each feedback group (i.e., the number of solutions
   * that would produce the same feedback if the guess were made).
   * - Identify the worst-case group size (the maximum number of remaining
   * solutions in any feedback group).
   *
   * The guess selected is the one that minimizes this worst-case group size,
   * ensuring steady progress toward solving the code.
   *
   * @return std::set<std::vector<int>> The set of potential next guesses,
   * ranked by their effectiveness in minimizing the search space.
   */
  std::set<std::vector<int>> Minimax();

  /**
   * @brief Get the maximum score from the feedback distribution.
   *
   * Represents the worst-case scenario for a given guess. The max score is
   * determined by evaluating the size of each feedback group that would result
   * from the guess and selecting the largest group. This score quantifies the
   * most possible solutions that could remain after making the guess and
   * receiving the least helpful feedback.
   *
   * @param score_count A map where each key is a feedback type (as a string)
   * and each value is the number of solutions that produce that feedback.
   * @return int The maximum score, representing the worst-case number of
   * remaining solutions for the given guess.
   */
  int GetMaxScore(const std::map<std::string, int> &score_count);

  /**
   * @brief Get the minimum score across all possible guesses.
   *
   * After calculating the max score for all possible guesses, this function
   * identifies the guess with the smallest max score. This represents the most
   * strategic choice: the guess that minimizes the worst-case number of
   * remaining possibilities, effectively reducing the search space and ensuring
   * steady progress toward the solution.
   *
   * @param score A map where each key is a possible guess (as a vector) and
   * each value is the max score for that guess.
   * @return int The minimum max score, representing the best guess for the
   * current state.
   */
  int GetMinScore(const std::map<std::vector<int>, int> &score);
};
} // namespace player

#endif // PLAYER_PLAYER_TYPE_CODEMASTER_CODEBREAKER_H_
