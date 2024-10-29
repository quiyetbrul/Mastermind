#include "util.h"

#include "ui/print.h"
#include "util/util.h"

std::string GiveFeedback(std::vector<int> guess, std::vector<int> code) {
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
  for (const int &code_element : code) {
    if (code_element > 0) { // If the code element hasn't been processed
      auto it = std::find(guess.begin(), guess.end(), code_element);
      if (it != guess.end()) { // If the color is found in the guess
        result.append("W");    // Append "W" for a white peg
        *it *= -1;             // Mark the guess as processed
      }
    }
  }

  return result; // Return the result string (e.g., "BWW")
}

void PrintGuesses(
    const std::vector<std::pair<std::vector<int>, std::string>> &guesses) {
  Title();
  for (const auto &i : guesses) {
    for (const auto &c : i.first) {
      std::cout << c << " ";
    }
    std::cout << "   " << i.second << std::endl;
  }
}

void PrintCode(std::vector<int> code) {
  for (const auto &i : code) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}
