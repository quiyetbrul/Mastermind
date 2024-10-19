#include "codebreaker.h"
#include <algorithm>
#include <iostream>

// Constructor initializes the codebreaker with code length and range of digits
Codebreaker::Codebreaker(const int &code_length, const int &min_digit,
                         const int &max_digit)
    : code_length_(code_length), min_digit_(min_digit), max_digit_(max_digit) {
  GenerateAllGuesses();
  current_guess_ = possible_guesses_.front(); // Initial guess
}

// Generates all possible guesses based on the code length and digit range
void Codebreaker::GenerateAllGuesses() {
  std::string code(code_length_, min_digit_ + '0');
  while (true) {
    possible_guesses_.push_back(code);

    // Generate the next permutation by incrementing digits
    int i = code_length_ - 1;
    while (i >= 0 && code[i] == max_digit_ + '0') {
      code[i] = min_digit_ + '0';
      --i;
    }
    if (i < 0)
      break; // If all combinations have been generated
    ++code[i];
  }
}

// Generates the next guess based on current state
std::string Codebreaker::MakeGuess() {
  return current_guess_; // Current guess is returned
}

// Processes the feedback and refines the possible guesses
void Codebreaker::ReceiveFeedback(const std::string &feedback) {
  // Filter out impossible guesses based on feedback
  FilterGuessesBasedOnFeedback(feedback);

  // Choose the next guess (just select the first remaining one for simplicity)
  if (!possible_guesses_.empty()) {
    current_guess_ = possible_guesses_.front();
  } else {
    std::cerr << "No more possible guesses!" << std::endl;
  }
}

// Filters possible guesses based on the feedback from the last guess
void Codebreaker::FilterGuessesBasedOnFeedback(const std::string &feedback) {
  std::vector<std::string> filtered_guesses;

  // Loop through each possible guess and keep only those that match the
  // feedback
  for (const auto &guess : possible_guesses_) {
    // Process feedback to see if it matches the guess
    int blackPegs = 0, whitePegs = 0;
    std::unordered_map<char, int> code_digit_count, guess_digit_count;

    // First pass: count black pegs (correct digit and position)
    for (int i = 0; i < code_length_; ++i) {
      if (guess[i] == current_guess_[i]) {
        blackPegs++;
      } else {
        code_digit_count[current_guess_[i]]++;
        guess_digit_count[guess[i]]++;
      }
    }

    // Second pass: count white pegs (correct digit but wrong position)
    for (auto &entry : guess_digit_count) {
      whitePegs += std::min(entry.second, code_digit_count[entry.first]);
    }

    // If this guess results in the same feedback, keep it
    if (std::to_string(blackPegs) + "," + std::to_string(whitePegs) ==
        feedback) {
      filtered_guesses.push_back(guess);
    }
  }

  // Update the possible guesses
  possible_guesses_ = filtered_guesses;
}
