/**
 * @file codebreaker.cpp
 * @brief Implementation of the Codebreaker class.
 */

#include "codebreaker.h"

#include <algorithm>
#include <climits>
#include <cmath>

#include "player/util/util.h"

namespace player {
Codebreaker::Codebreaker(int code_length, int min_digit, int max_digit)
    : code_length_(code_length), min_digit_(min_digit), max_digit_(max_digit) {
  GenerateCombinations();
}

std::vector<int> Codebreaker::MakeGuess() {
  std::set<std::vector<int>> nextGuesses = Minimax();

  // Check if any of the next guesses are in the candidate solutions
  for (const auto &guess : nextGuesses) {
    if (candidate_solutions_.contains(guess)) {
      return guess;
    }
  }

  // If no next guess is found in candidate solutions, return the first next
  // guess
  if (!nextGuesses.empty()) {
    return *nextGuesses.begin();
  }

  return {};
}

void Codebreaker::GenerateCombinations() {
  std::vector<int> current(code_length_);
  int total_combinations =
      std::pow((max_digit_ - min_digit_ + 1), code_length_);

  // Generate all possible combinations of the code
  for (int i = 0; i < total_combinations; ++i) {
    int temp = i;
    for (int j = 0; j < code_length_; ++j) {
      current[j] = min_digit_ + (temp % (max_digit_ - min_digit_ + 1));
      temp /= (max_digit_ - min_digit_ + 1);
    }
    combinations_.insert(current);
    candidate_solutions_.insert(current);
  }
}

void Codebreaker::RemoveCode(const std::vector<int> &guess) {
  combinations_.erase(guess);
  candidate_solutions_.erase(guess);
}

void Codebreaker::FilterSolutions(const std::vector<int> &guess,
                                  const std::string &feedback) {
  if (feedback.empty()) {
    // Remove solutions containing any element in guess
    std::set<int> guess_set(guess.begin(), guess.end());
    std::erase_if(candidate_solutions_,
                  [&guess_set](const std::vector<int> &solution) {
                    return std::any_of(solution.begin(), solution.end(),
                                       [&guess_set](int element) {
                                         return guess_set.count(element) > 0;
                                       });
                  });
  } else {
    // Remove solutions that do not produce the same feedback
    std::erase_if(candidate_solutions_, [&guess, &feedback, this](
                                            const std::vector<int> &solution) {
      return feedback != player::GiveFeedback(guess, solution, code_length_);
    });
  }
}
std::set<std::vector<int>> Codebreaker::Minimax() {
  std::map<std::string, int> score_count;  // count of each feedback score
  std::map<std::vector<int>, int> score;   // maximum score for each guess
  std::set<std::vector<int>> next_guesses; // potential next guesses
  int max = INT_MIN;
  int min = INT_MAX;

  for (const auto &i : combinations_) {
    for (const auto &j : candidate_solutions_) {
      std::string peg_score = player::GiveFeedback(i, j, code_length_);
      score_count[peg_score]++;
    }
    max = GetMaxScore(score_count);
    score_count.clear();
    score[i] = max;
  }

  min = GetMinScore(score);
  for (const auto &entry : score) {
    if (entry.second == min) {
      next_guesses.insert(entry.first);
    }
  }
  return next_guesses;
}

int Codebreaker::GetMaxScore(const std::map<std::string, int> &input_map) {
  int max = INT_MIN;

  // Iterate over the input map to find the max value
  for (const auto &entry : input_map) {
    if (entry.second > max) {
      max = entry.second;
    }
  }
  return max;
}

int Codebreaker::GetMinScore(const std::map<std::vector<int>, int> &input_map) {
  int min = INT_MAX;

  // Iterate over the input map to find the min value
  for (const auto &entry : input_map) {
    if (entry.second < min) {
      min = entry.second;
    }
  }
  return min;
}
} // namespace player
