/**
 * @file codebreaker.cpp
 * @brief Implementation of the Codebreaker class.
 */

#include "codebreaker.h"

#include <algorithm>
#include <climits>
#include <string>

#include "player/util/util.h"

namespace game_type {
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
  std::vector<int> current(code_length_, 0);
  GenerateCombinations(0, current);
  candidate_solutions_.insert(candidate_solutions_.end(), combinations_.begin(),
                              combinations_.end());
}

void Codebreaker::GenerateCombinations(int position,
                                       std::vector<int> &current) {
  if (position >= code_length_) {
    combinations_.push_back(current);
    return;
  }

  for (int i = min_digit_; i <= max_digit_; ++i) {
    current[position] = i;
    GenerateCombinations(position + 1, current);
  }
}

void Codebreaker::RemoveCode(const std::vector<int> &guess) {
  if (guess.empty()) {
    return;
  }
  RemoveCode(combinations_, guess);
  RemoveCode(candidate_solutions_, guess);
}

void Codebreaker::RemoveCode(std::vector<std::vector<int>> &set,
                             const std::vector<int> &guess) {
  for (auto it = set.begin(); it != set.end(); it++) {
    // Find the index of the current iterator
    int index = std::distance(set.begin(), it);

    // Remove the code from the set if it matches the guess
    if (set[index] == guess) {
      set.erase(set.begin() + index);
      break;
    }
  }
}

void Codebreaker::FilterSolutions(const std::vector<int> &guess,
                                  const std::string &feedback) {
  int index;
  for (auto it = candidate_solutions_.begin();
       it != candidate_solutions_.end();) {
    if (feedback != player::GiveFeedback(guess, *it, code_length_)) {
      it = candidate_solutions_.erase(it);
    } else {
      ++it;
    }
  }
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
} // namespace game_type
