#include "codebreaker.h"

#include <algorithm>
#include <climits>
#include <string>

#include "player/util/util.h"

namespace player {
// Constructor
Codebreaker::Codebreaker(int code_length, int min_digit, int max_digit)
    : code_length_(code_length), min_digit_(min_digit), max_digit_(max_digit) {
  // Initialize possible guesses (for example, generate all permutations)
  CreateSet();
}

std::vector<int> Codebreaker::MakeGuess() {
  std::vector<std::vector<int>> nextGuesses = Minimax();
  std::vector<int> nextGuess;

  for (int i = 0; i < nextGuesses.size(); ++i) {
    if (find(candidate_solutions_.begin(), candidate_solutions_.end(),
             nextGuesses[i]) != candidate_solutions_.end()) {
      return nextGuesses[i];
    }
  }
  for (int j = 0; j < nextGuesses.size(); ++j) {
    if (find(combinations_.begin(), combinations_.end(), nextGuesses[j]) !=
        combinations_.end()) {
      return nextGuesses[j];
    }
  }

  return nextGuess;
}

void Codebreaker::CreateSet() {
  std::vector<int> current(code_length_, 0);
  std::vector<int> elements;
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
  int index;
  for (auto it = set.begin(); it != set.end(); it++) {
    index = std::distance(set.begin(),
                          it); // Find the index of the current iterator

    if (set[index] == guess) { // If the current code matches the one to remove
      set.erase(set.begin() + index); // Remove the code from the set
      break;
    }
  }
}

void Codebreaker::PruneCodes(const std::vector<int> &guess,
                             const std::string &feedback) {
  candidate_solutions_.erase(
      std::remove_if(candidate_solutions_.begin(), candidate_solutions_.end(),
                     [&](const std::vector<int> &code) {
                       return feedback !=
                              player::GiveFeedback(guess, code, code_length_);
                     }),
      candidate_solutions_.end());
}

std::vector<std::vector<int>> Codebreaker::Minimax() {
  std::map<std::string, int> score_count;
  std::map<std::vector<int>, int> score;
  std::vector<std::vector<int>> next_guesses;
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
  int max = INT_MIN; // Stores the maximum score found

  // Iterate over the input map to find the max value
  for (const auto &entry : inputMap) {
    if (entry.second > max) {
      max = entry.second;
    }
  }
  return max;
}

int Codebreaker::GetMinScore(const std::map<std::vector<int>, int> &inputMap) {
  int min = INT_MAX; // Stores the minimum score found

  // Iterate over the input map to find the min value
  for (const auto &entry : inputMap) {
    if (entry.second < min) {
      min = entry.second;
    }
  }
  return min;
}
} // namespace player
