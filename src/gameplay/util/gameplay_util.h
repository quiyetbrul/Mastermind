#ifndef GAMEPLAY_UTIL_H_
#define GAMEPLAY_UTIL_H_

#include <string>
#include <vector>

#include "util.h"

// Custom hash function for std::vector<int>
struct VectorHash {
  std::size_t operator()(const std::vector<int> &v) const {
    std::size_t seed = v.size();
    for (auto &i : v) {
      seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
  }
};

inline std::string GiveFeedback(std::vector<int> guess, std::vector<int> code) {

  std::string result; // Stores the result of checking the guess

  // Check for exact matches (colored pegs)
  for (int i = 0; i < kSecretCodeLength; ++i) {

    if (guess[i] == code[i]) { // If the guess matches the code at this position
      result.append("B");      // Append "B" for a black (colored) peg
      guess[i] *= -1;          // Mark this position as processed
      code[i] *= -1;           // Mark this position as processed
    }
  }

  // Check for white pegs (correct color but wrong position)
  for (int i = 0; i < kSecretCodeLength; ++i) {

    if (code[i] > 0) { // If the code element hasn't been processed

      std::vector<int>::iterator it = find(guess.begin(), guess.end(), code[i]);
      int index;
      if (it != guess.end()) { // If the color is found in the guess

        index =
            distance(guess.begin(), it); // Get the index of the matching guess
        result.append("W");              // Append "W" for a white peg
        guess[index] *= -1;              // Mark the guess as processed
      }
    }
  }

  return result; // Return the result string (e.g., "BWW")
}

#endif // GAMEPLAY_UTIL_H_
