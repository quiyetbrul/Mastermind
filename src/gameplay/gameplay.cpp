#include "gameplay.h"

#include <iostream>
#include <string>

#include "../ui/menu.h"
#include "../ui/print.h"
#include "../util/util.h"

Gameplay::Gameplay() {}

void Gameplay::Start() {
  int menu_choice = MainMenu();
  switch (menu_choice) {
  case 1:
    Game();
    break;
  case 2:
    Instructions();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    Start();
    break;
  case 3:
    Goodbye();
    CloseTerminal();
    break;
  }
}

void Gameplay::Game() {
  int player_choice = PlayerMenu();
  switch (player_choice) {
  case 1:
    SinglePlayer();
    break;
  case 2:
    MultiPlayer();
    break;
  }
}

void Gameplay::SinglePlayer() {
  Title();

  std::string secret_code =
      GenRandom(kSecretCodeLength, kMinSecretCodeDigit, kMaxSecretCodeDigit);
  std::cout << secret_code << std::endl;
  int life = 10;
  int i = 0;

  // TODO: ask whether history is a an option while in game
  // or leaving previous guesses visible on the screen suffices

  while (life > 0) {
    std::string user_guess = InputGuess("Enter your guess: ");

    if (user_guess == secret_code) {
      Congratulations();
      break;
    } else {
      // TODO: make this a function
      // maybe make it look better
      for (const auto &i : user_guess) {
        std::cout << i << "  ";
      }
      std::cout << GiveFeedback(secret_code, user_guess) << std::endl;
      --life;
    }
    if (life == 0) {
      TryAgain();
    }
  }

  PlayAgain();
}

void Gameplay::MultiPlayer() {
  std::cout << "Multiplayer" << std::endl;
  PlayAgain();
}

void Gameplay::PlayAgain() {
  char play_again = InputChar("Do you want to play again? (y/n): ", 'y', 'n');
  if (play_again == 'y') {
    Game();
  } else {
    // TODO: maybe we just exit out of program?
    Start();
  }
}

std::string Gameplay::GiveFeedback(const std::string &secret_code,
                                   const std::string &guesses) {
  int correct_position = 0;
  int correct_digit = 0;

  // Vectors to keep track of unmatched digits
  std::vector<bool> matched_secret(kSecretCodeLength, false);
  std::vector<bool> matched_guess(kSecretCodeLength, false);
  std::array<int, 10> secret_count = {0};

  // First pass: mark exact matches and count remaining digits in secret_code
  for (int i = 0; i < kSecretCodeLength; i++) {
    if (guesses[i] == secret_code[i]) {
      correct_position++;
      matched_secret[i] = true;
      matched_guess[i] = true;
    } else {
      secret_count[secret_code[i] - '0']++;
    }
  }

  // Second pass: count correct digits in wrong positions
  for (int i = 0; i < kSecretCodeLength; i++) {
    if (!matched_guess[i] && secret_count[guesses[i] - '0'] > 0) {
      correct_digit++;
      secret_count[guesses[i] - '0']--;
    }
  }

  if (correct_position == 0 && correct_digit == 0) {
    return std::string(ANSI_COLOR_RED) + "No correct digit\n" + ANSI_RESET;
  }

  std::string feedback = "";
  for (int i = 0; i < correct_position; i++) {
    feedback += std::string(ANSI_COLOR_GREEN) + "X" + ANSI_RESET;
  }

  for (int i = 0; i < correct_digit; i++) {
    feedback += std::string(ANSI_COLOR_YELLOW) + "O" + ANSI_RESET;
  }

  return feedback;
}
