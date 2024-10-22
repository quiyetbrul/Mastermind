#include "gameplay_util.h"

#include <iostream>

#include "ui/print.h"
#include "util/util.h"

void PlayGameLoop(Player &player, Codebreaker *computer,
                  std::vector<int> initial_guess) {
  std::vector<int> guess = initial_guess;

  while (player.GetLife() > 0) {

    if (!computer) {
      guess = InputGuess("Enter your guess: ");
    }

    if (guess == player.GetSecretCode()) {
      Congratulations();
      PrintCode(player.GetSecretCode());
      player.SetWinner(true);
      break;
    }

    std::string feedback = GiveFeedback(player.GetSecretCode(), guess);
    player.AddGuess(guess, feedback);
    PrintGuesses(player.GetGuesses());
    player.DecrementLife();

    if (player.GetLife() == 0) {
      TryAgain();
      PrintCode(player.GetSecretCode());
      player.SetWinner(false);
      break;
    }

    if (computer) {
      computer->RemoveCode(guess);           // Remove the guess from the set
      computer->PruneCodes(guess, feedback); // Prune the set of codes
      guess = computer->MakeGuess();         // Use MakeGuess to get a guess
    }
  }
}

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
  for (int &code_element : code) {
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
