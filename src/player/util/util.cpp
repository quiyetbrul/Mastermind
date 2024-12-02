/**
 * @file util.cpp
 * @brief Implementation for utility functions used by the player.
 */

#include <unordered_map>

#include "util.h"

namespace player {

#define COLOR_MASTERMIND 8

std::string GiveFeedback(const std::vector<int> &guess,
                         const std::vector<int> &code,
                         const int &secret_code_length) {
  std::string result;
  std::unordered_map<int, int> code_counts;
  std::unordered_map<int, int> guess_counts;

  // First pass: check for black pegs (exact matches)
  for (int i = 0; i < secret_code_length; ++i) {
    if (guess[i] == code[i]) {
      result.append("B");
    } else {
      // Count digits for potential white pegs
      code_counts[code[i]]++;
      guess_counts[guess[i]]++;
    }
  }

  // Second pass: check for white pegs (correct digit, wrong position)
  for (int i = 0; i < secret_code_length; ++i) {
    if (guess[i] != code[i]) { // Only consider non-exact matches
      if (code_counts.contains(guess[i]) && code_counts[guess[i]] > 0) {
        result.append("W");
        code_counts[guess[i]]--; // Use one occurrence of this digit
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
