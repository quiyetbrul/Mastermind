/**
 * @file util.cpp
 * @brief Implementation for utility functions used by the player.
 */

#include "util.h"

namespace player {

#define COLOR_MASTERMIND 8

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

  // Second pass: check for white pegs (correct digit, wrong position)
  for (int i = 0; i < secret_code_length; ++i) {
    if (!code_used[i]) { // Only consider unused code positions
      for (int j = 0; j < secret_code_length; ++j) {
        if (!guess_used[j] &&
            code[i] == guess[j]) { // Find unused matching digit
          result.append("W");
          guess_used[j] = true; // Mark this guess position as used
          break;
        }
      }
    }
  }

  return result;
}

std::string GiveHint(const std::vector<int> &guess,
                     const std::vector<int> &code) {
  std::string hint;

  for (int i = 0; i < guess.size(); i++) {
    if (guess[i] != code[i]) {
      hint = "Position " + std::to_string(i + 1) + " needs to be " +
             (guess[i] > code[i] ? "lower" : "higher");
      break;
    }
  }

  return hint;
}
} // namespace player
