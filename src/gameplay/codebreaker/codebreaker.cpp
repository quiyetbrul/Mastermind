#include "codebreaker.h"

#include <climits>
#include <string>

// Constructor
Codebreaker::Codebreaker(int code_length, int min_digit, int max_digit)
    : code_length_(code_length), min_digit_(min_digit), max_digit_(max_digit) {
  // Initialize possible guesses (for example, generate all permutations)
  createSet();
}

std::vector<int> Codebreaker::MakeGuess() {
  std::vector<std::vector<int>> nextGuesses = minimax();
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

void Codebreaker::createSet() {
  std::vector<int> current(code_length_, 0);
  std::vector<int> elements;
  generateCombinations(0, current);
  candidate_solutions_.insert(candidate_solutions_.end(), combinations_.begin(),
                              combinations_.end());
}

void Codebreaker::generateCombinations(int position,
                                       std::vector<int> &current) {
  if (position >= code_length_) {
    combinations_.push_back(current);
    return;
  }

  for (int i = min_digit_; i <= max_digit_; ++i) {
    current[position] = i;
    generateCombinations(position + 1, current);
  }
}

void Codebreaker::removeCode(const std::vector<int> &guess) {
  if (guess.empty()) {
    return;
  }
  int index;
  for (auto it = combinations_.begin(); it != combinations_.end(); it++) {
    index = std::distance(combinations_.begin(),
                          it); // Find the index of the current iterator

    if (combinations_[index] ==
        guess) { // If the current code matches the one to remove
      combinations_.erase(combinations_.begin() +
                          index); // Remove the code from the set
      break;
    }
  }
  for (auto it = candidate_solutions_.begin(); it != candidate_solutions_.end();
       it++) {
    index = std::distance(candidate_solutions_.begin(),
                          it); // Find the index of the current iterator

    if (candidate_solutions_[index] ==
        guess) { // If the current code matches the one to remove
      candidate_solutions_.erase(candidate_solutions_.begin() +
                                 index); // Remove the code from the set
      break;
    }
  }
}

void Codebreaker::pruneCodes(const std::vector<int> &guess,
                             const std::string &feedback) {
  int index;
  auto it = candidate_solutions_.begin();

  // Iterate through the set of codes
  while (it != candidate_solutions_.end()) {
    index = distance(candidate_solutions_.begin(), it);

    // If the code's response doesn't match the expected response, remove it
    if (feedback != checkCode(guess, candidate_solutions_[index])) {
      it = candidate_solutions_.erase(candidate_solutions_.begin() + index);
    } else {
      it++; // Move to the next code
    }
  }
}

std::string Codebreaker::checkCode(std::vector<int> guess,
                                   std::vector<int> secret_code) {
  std::string result; // Stores the result of checking the guess

  // Check for exact matches (colored pegs)
  for (int i = 0; i < code_length_; ++i) {

    if (guess[i] == secret_code[i]) { // If the guess matches the secret_code at
                                      // this position
      result.append("B");             // Append "B" for a black (colored) peg
      guess[i] *= -1;                 // Mark this position as processed
      secret_code[i] *= -1;           // Mark this position as processed
    }
  }

  // Check for white pegs (correct color but wrong position)
  for (int i = 0; i < code_length_; ++i) {

    if (secret_code[i] >
        0) { // If the secret_code element hasn't been processed

      auto it = find(guess.begin(), guess.end(), secret_code[i]);
      int index;
      if (it != guess.end()) { // If the color is found in the guess

        index = std::distance(guess.begin(),
                              it); // Get the index of the matching guess
        result.append("W");        // Append "W" for a white peg
        guess[index] *= -1;        // Mark the guess as processed
      }
    }
  }

  return result; // Return the result string (e.g., "BWW")
}

std::vector<std::vector<int>> Codebreaker::minimax() {
  std::map<std::string, int> score_count;
  std::map<std::vector<int>, int> score;
  std::vector<std::vector<int>> next_guesses;
  int max = INT_MIN;
  int min = INT_MAX;
  for (auto &i : combinations_) {
    for (auto &j : candidate_solutions_) {
      std::string peg_score = checkCode(i, j);
      if (score_count.count(peg_score) > 0) {
        score_count[peg_score] += 1;
      } else {
        score_count[peg_score] = 1;
      }
    }
    max = getMaxScore(score_count);
    score_count.clear();
    score.insert({i, max});
  }

  min = getMinScore(score);
  for (auto &entry : score) {
    if (entry.second == min) {
      next_guesses.push_back(entry.first);
    }
  }
  return next_guesses;
}

int Codebreaker::getMaxScore(const std::map<std::string, int> &inputMap) {

  int max = INT_MIN; // Stores the maximum score found

  // Iterate over the input map to find the max value
  for (auto it = inputMap.begin(); it != inputMap.end(); ++it) {

    if (it->second > max) {
      max = it->second;
    }
  }

  return max; // Return the max value
}

int Codebreaker::getMinScore(const std::map<std::vector<int>, int> &inputMap) {

  int min = INT_MAX; // Initialize to a large value

  // Iterate over the input map to find the min value
  for (auto it = inputMap.begin(); it != inputMap.end(); ++it) {

    if (it->second < min) {
      min = it->second;
    }
  }

  return min; // Return the min value
}
