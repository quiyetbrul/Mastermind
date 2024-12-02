/**
 * @file codebreaker.cpp
 * @brief Implementation of the Codebreaker class.
 */

#include "codebreaker.h"

#include <algorithm>
#include <climits>
#include <string>

#include "player/util/util.h"

namespace player {
Codebreaker::Codebreaker(int code_length, int min_digit, int max_digit)
    : code_length_(code_length), min_digit_(min_digit), max_digit_(max_digit) {
  Init();
}

std::vector<int> Codebreaker::MakeGuess() {
  std::vector<std::vector<int>> nextGuesses = Minimax();
  std::vector<int> nextGuess;

  // Check if any of the next guesses are in the candidate solutions
  for (const auto &guess : nextGuesses) {
    if (std::find(candidate_solutions_.begin(), candidate_solutions_.end(),
                  guess) != candidate_solutions_.end()) {
      return guess;
    }
  }

  // If no next guess is found in candidate solutions, return the first next
  // guess
  if (!nextGuesses.empty()) {
    return nextGuesses[0];
  }

  return nextGuess;
}

void Codebreaker::Init() {
  GenerateCombinations();
  candidate_solutions_.insert(combinations_.begin(), combinations_.end());
}

void Codebreaker::GenerateCombinations() {
  std::vector<int> current(code_length_);
  int total_combinations =
      std::pow((max_digit_ - min_digit_ + 1), code_length_);

  // Generate combinations using a loop instead of recursion
  for (int i = 0; i < total_combinations; ++i) {
    int temp = i;
    for (int j = 0; j < code_length_; ++j) {
      current[j] = min_digit_ + (temp % (max_digit_ - min_digit_ + 1));
      temp /= (max_digit_ - min_digit_ + 1);
    }
    combinations_.insert(current);
  }
}

void Codebreaker::RemoveCode(const std::vector<int> &guess) {
  if (guess.empty()) {
    return;
  }
  RemoveCode(combinations_, guess);
  RemoveCode(candidate_solutions_, guess);
}

void Codebreaker::RemoveCode(std::set<std::vector<int>> &set,
                             const std::vector<int> &guess) {
  for (auto it = set.begin(); it != set.end(); it++) {
    // Find the index of the current iterator
    int index = std::distance(set.begin(), it);

    // Remove the code from the set if it matches the guess
    if (*it == guess) {
      set.erase(it);
      break;
    }
  }
}

void Codebreaker::FilterSolutions(const std::vector<int> &guess,
                                  const std::string &feedback) {
  std::erase_if(candidate_solutions_, [&guess, &feedback,
                                       this](const std::vector<int> &solution) {
    return feedback != player::GiveFeedback(guess, solution, code_length_);
  });
}

std::vector<std::vector<int>> Codebreaker::Minimax() {
  std::map<std::string, int> score_count;     // count of each feedback score
  std::map<std::vector<int>, int> score;      // maximum score for each guess
  std::vector<std::vector<int>> next_guesses; // potential next guesses
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
      next_guesses.push_back(entry.first);
    }
  }
  return next_guesses;
}

int Codebreaker::GetMaxScore(const std::map<std::string, int> &inputMap) {
  int max = INT_MIN;

  // Iterate over the input map to find the max value
  for (const auto &entry : inputMap) {
    if (entry.second > max) {
      max = entry.second;
    }
  }
  return max;
}

int Codebreaker::GetMinScore(const std::map<std::vector<int>, int> &inputMap) {
  int min = INT_MAX;

  // Iterate over the input map to find the min value
  for (const auto &entry : inputMap) {
    if (entry.second < min) {
      min = entry.second;
    }
  }
  return min;
}
} // namespace player
