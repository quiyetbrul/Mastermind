#include "util.h"

#include <iostream>

std::vector<int> InputGuess(const std::string &prompt, int secret_code_length,
                            int secret_code_min_digit,
                            int secret_code_max_digit) {
  std::string input;
  while (true) {
    std::cout << prompt;
    std::cin >> input;

    if (input.length() != secret_code_length) {
      std::cout << "Input must be exactly " << secret_code_length
                << " digits long." << std::endl;
      continue;
    }

    if (!std::all_of(input.begin(), input.end(),
                     [secret_code_min_digit, secret_code_max_digit](char c) {
                       return c >= '0' + secret_code_min_digit &&
                              c <= '0' + secret_code_max_digit;
                     })) {
      std::cout << "Each digit must be between " << secret_code_min_digit
                << " and " << secret_code_max_digit << "." << std::endl;
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
                         const std::vector<int> &code,
                         const int &secret_code_length) {
  std::string result;
  std::vector<bool> guess_used(secret_code_length, false);
  std::vector<bool> code_used(secret_code_length, false);

  // First pass: check for black pegs (exact matches)
  for (int i = 0; i < secret_code_length; ++i) {
    if (guess[i] == code[i]) {
      result.append("B");
      guess_used[i] = true; // Mark this guess position as used
      code_used[i] = true;  // Mark this code position as used
    }
  }

  // Second pass: check for white pegs (correct color, wrong position)
  for (int i = 0; i < secret_code_length; ++i) {
    if (!code_used[i]) { // Only consider unused code positions
      for (int j = 0; j < secret_code_length; ++j) {
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
