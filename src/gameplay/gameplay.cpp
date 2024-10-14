#include "gameplay.h"

#include <iostream>

#include "../ui/menu.h"
#include "../ui/print.h"
#include "../util/util.h"

const int kMinSecretCode = 0;
const int kMaxSecretCodeDigit = 7;
const int kSecretCodeLength = 4;

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
  std::vector<int> secretCode{0, 1, 3, 5};
  // TODO: uncomment this to generate a random secret code
  // for (int i = 0; i < kSecretCodeLength; i++) {
  //   secretCode.push_back(GenRandom(kMinSecretCode, kMaxSecretCodeDigit));
  // }
  // for (const auto &i : secretCode) {
  //   std::cout << i;
  // }
  // std::cout << std::endl;
  int life = 10;
  std::unordered_map<int, std::vector<int>> guessHistory;
  int i = 0;

  while (true) {
    // todo input validation for user input of 4 digits
    // length
    // isdigit
    // each digit is between 0 and 7
    std::string userGuess;
    std::cout << "enter your guess: ";
    std::cin >> userGuess;

    // separate the user input into a vector of integers
    std::vector<int> userGuessVector;
    for (int i = 0; i < kSecretCodeLength; i++) {
      userGuessVector.push_back(userGuess[i] - '0');
    }

    guessHistory[i++] = userGuessVector;

    std::cout << "player guessed: " << userGuess << std::endl;

    if (userGuessVector == secretCode) {
      Congratulations();
      PlayAgain();
    } else if (life > 0) {
      std::cout << GiveFeedback(secretCode, userGuessVector) << std::endl;
      life--;
    } else {
      break;
    }
  }

  TryAgain();
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

// TODO: should probably be public and return a string instead of printing
// for testing
std::string Gameplay::GiveFeedback(const std::vector<int> &secretCode,
                                   const std::vector<int> &guesses) {
  int correctPosition = 0;
  int correctDigit = 0;

  for (int i = 0; i < kSecretCodeLength; i++) {
    if (guesses[i] == secretCode[i]) {
      correctPosition++;
    }
  }

  // TODO: just pass this as a parameter
  std::unordered_map<int, int> secretCodeCount;
  for (const auto &i : secretCode) {
    secretCodeCount[i]++;
  }

  for (const auto &i : guesses) {
    if (secretCodeCount.find(i) != secretCodeCount.end() &&
        secretCodeCount[i] > 0) {
      correctDigit++;
      secretCodeCount[i]--;
    }
  }

  std::string feedback =
      std::string(ANSI_COLOR_RED) + "No correct digit\n" + ANSI_COLOR_RESET;
  if (correctPosition == 0 && correctDigit == 0) {
    return feedback;
  }

  feedback = "";
  for (int i = 0; i < correctPosition; i++) {
    feedback += std::string(ANSI_COLOR_GREEN) + "X" + ANSI_COLOR_RESET;
  }

  for (int i = 0; i < correctDigit - correctPosition; i++) {
    feedback += std::string(ANSI_COLOR_YELLOW) + "O" + ANSI_COLOR_RESET;
  }

  return feedback;
}
