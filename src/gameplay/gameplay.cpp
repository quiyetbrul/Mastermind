#include "gameplay.h"

#include <iostream>

#include "../ui/menu.h"
#include "../ui/print.h"
#include "../util/util.h"

Gameplay::Gameplay() {}

void Gameplay::Start() {
  int menuChoice = Menu();
  switch (menuChoice) {
  case 1:
    Game();
    break;
  case 2:
    Instructions();
    // TODO: Add a prompt to go back to the main menu
    break;
  case 3:
    Goodbye();
    CloseTerminal();
    break;
  }
}

void Gameplay::Game() {
  Title();

  std::string secretCode = "";
  for (int i = 0; i < kSecretCodeLength; i++) {
    secretCode +=
        std::to_string(GenRandom(kMinSecretCodeDigit, kMaxSecretCodeDigit));
  }
  std::cout << secretCode << std::endl;
  int life = 10;
  // TODO: ask whether this is a an option while in game
  // or leaving previous guesses visible on the screen suffices
  std::unordered_map<int, std::vector<int>> guessHistory;
  int i = 0;

  std::vector<int> secretCodeCount{kSecretCodeLength, 0};
  for (const auto &i : secretCode) {
    secretCodeCount[i]++;
  }

  while (life > 0) {
    std::string userGuess = InputGuess("Enter your guess: ");

    if (userGuess == secretCode) {
      Congratulations();
      break;
    } else {
      // TODO: make this a function
      // maybe make it look better
      for (const auto &i : userGuess) {
        std::cout << i << "  ";
      }
      std::cout << GiveFeedback(secretCode, userGuess) << std::endl;
      --life;
    }
    if (life == 0) {
      TryAgain();
    }
  }

  PlayAgain();
}

void Gameplay::PlayAgain() {
  char playAgain = InputChar("Do you want to play again? (y/n): ", 'y', 'n');
  if (playAgain == 'y') {
    Game();
  } else {
    // TODO: maybe we just exit out of program?
    Start();
  }
}

std::string Gameplay::GiveFeedback(const std::string &secretCode,
                                   const std::string &guesses) {
  int correctPosition = 0;
  int correctDigit = 0;

  // Vectors to keep track of unmatched digits
  std::vector<bool> matchedSecret(kSecretCodeLength, false);
  std::vector<bool> matchedGuess(kSecretCodeLength, false);

  // Count correct positions
  for (int i = 0; i < kSecretCodeLength; i++) {
    if (guesses[i] == secretCode[i]) {
      correctPosition++;
      matchedSecret[i] = true;
      matchedGuess[i] = true;
    }
  }

  // Count correct digits
  for (int i = 0; i < kSecretCodeLength; i++) {
    if (!matchedGuess[i]) {
      for (int j = 0; j < kSecretCodeLength; j++) {
        if (!matchedSecret[j] && guesses[i] == secretCode[j]) {
          correctDigit++;
          matchedSecret[j] = true;
          break;
        }
      }
    }
  }

  if (correctPosition == 0 && correctDigit == 0) {
    return std::string(ANSI_COLOR_RED) + "No correct digit\n" + ANSI_RESET;
  }

  std::string feedback = "";
  for (int i = 0; i < correctPosition; i++) {
    feedback += std::string(ANSI_COLOR_GREEN) + "X" + ANSI_RESET;
  }

  for (int i = 0; i < correctDigit; i++) {
    feedback += std::string(ANSI_COLOR_YELLOW) + "O" + ANSI_RESET;
  }

  return feedback;
}
