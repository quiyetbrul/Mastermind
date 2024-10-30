#include "util.h"

#include <iostream>

#include "util/util.h"

std::vector<int> InputGuess(const std::string &prompt) {
  std::string input;
  while (true) {
    std::cout << prompt;
    std::cin >> input;

    if (input.length() != kSecretCodeLength) {
      std::cout << "Input must be exactly " << kSecretCodeLength
                << " digits long." << std::endl;
      continue;
    }

    if (!std::all_of(input.begin(), input.end(),
                     [](char c) { return c >= '0' && c <= '7'; })) {
      std::cout << "Each digit must be between 0 and 7." << std::endl;
      continue;
    }

    break;
  }

  std::vector<int> result(input.begin(), input.end());
  std::transform(result.begin(), result.end(), result.begin(),
                 [](char c) { return c - '0'; });

  return result;
}

std::string GiveFeedback(const std::vector<int> &guess,
                         const std::vector<int> &code) {
  std::string result;
  std::vector<bool> guess_used(kSecretCodeLength, false);
  std::vector<bool> code_used(kSecretCodeLength, false);

  // First pass: check for black pegs (exact matches)
  for (int i = 0; i < kSecretCodeLength; ++i) {
    if (guess[i] == code[i]) {
      result.append("B");
      guess_used[i] = true; // Mark this guess position as used
      code_used[i] = true;  // Mark this code position as used
    }
  }

  // Second pass: check for white pegs (correct color, wrong position)
  for (int i = 0; i < kSecretCodeLength; ++i) {
    if (!code_used[i]) { // Only consider unused code positions
      for (int j = 0; j < kSecretCodeLength; ++j) {
        if (!guess_used[j] &&
            code[i] == guess[j]) { // Find unused matching color
          result.append("W");
          guess_used[j] = true; // Mark this guess position as used
          break;
        }
      }
    }
  }

  return result;
}

void PrintGuess(const std::vector<int> &guess, const std::string &feedback) {
  for (const auto &i : guess) {
    std::cout << i << " ";
  }
  std::cout << "   " << feedback << std::endl;
}

void PrintCode(std::vector<int> code) {
  for (const auto &i : code) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}
