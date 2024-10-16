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
    GameMenu();
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

void Gameplay::GameMenu() {
  // TODO: play as guest or register/login
  int player_choice = PlayerMenu();
  switch (player_choice) {
  case 1:
    SinglePlayer();
    break;
  case 2:
    ComputerCodebreaker();
    break;
  }
}

// TODO: need to add menu for when player wants to be codemaster
// computer can either use actual algo to solve the code or use GenRandom 10x
// can use minmax?
void Gameplay::SinglePlayer() {
  Title();

  std::string secret_code =
      GenRandom(kSecretCodeLength, kMinSecretCodeDigit, kMaxSecretCodeDigit);
  // TODO: remove cout
  // std::cout << secret_code << std::endl;
  int life = 10;
  int i = 0;

  std::vector<std::pair<std::string, std::string>> user_guess_history;

  while (life > 0) {
    std::string user_guess = InputGuess("Enter your guess: ");

    // TODO: if user_guess == "/save"
    // implement save func then return to main menu

    if (user_guess == secret_code) {
      Congratulations();
      break;
    }
    std::string feedback = GiveFeedback(secret_code, user_guess);
    user_guess_history.push_back(std::make_pair(user_guess, feedback));
    PrintGuesses(user_guess_history);
    if (--life == 0) {
      TryAgain();
      std::cout << secret_code << std::endl;
    }
  }

  PlayAgain();
}

void Gameplay::ComputerCodebreaker() {
  // TODO: implement donald knuth's 5-guess algo

  Title();

  std::string secret_code =
      GenRandom(kSecretCodeLength, kMinSecretCodeDigit, kMaxSecretCodeDigit);
  // TODO: remove cout
  // std::cout << secret_code << std::endl;
  int life = 10;
  int i = 0;

  std::vector<std::pair<std::string, std::string>> computer_guess_history;

  while (life > 0) {
    // TODO: it'll be the 5-guess algo
    std::string computer_guess = "";
    PrintGuesses(computer_guess_history);
    if (computer_guess == secret_code) {
      Congratulations();
      break;
    }
    if (--life == 0) {
      TryAgain();
      std::cout << secret_code << std::endl;
    }
  }

  PlayAgain();
}

void Gameplay::PlayAgain() {
  char play_again = InputChar("Do you want to play again? (y/n): ", 'y', 'n');
  if (play_again == 'y') {
    GameMenu();
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
    return std::string(ANSI_COLOR_RED) + "No correct digit" + ANSI_RESET;
  }

  std::string feedback = "";
  for (int i = 0; i < correct_position; i++) {
    feedback += std::string(ANSI_COLOR_GREEN) + "B" + ANSI_RESET;
  }

  for (int i = 0; i < correct_digit; i++) {
    feedback += std::string(ANSI_COLOR_YELLOW) + "W" + ANSI_RESET;
  }

  return feedback;
}

bool Gameplay::PrintGuesses(
    std::vector<std::pair<std::string, std::string>> &guesses) {
  Title();
  for (const auto &i : guesses) {
    for (const auto &c : i.first) {
      std::cout << c << " ";
    }
    std::cout << "   " << i.second << std::endl;
  }
  return false;
}

std::string Gameplay::InputString(const std::string &prompt) {
  std::cout << prompt;
  std::string input;
  std::cin >> input;
  return input;
}

std::string Gameplay::InputGuess(const std::string &prompt) {
  std::string input;
  while (true) {
    std::cout << prompt;
    std::cin >> input;

    // `std::string_view` offers better performance with string comparisons
    // by avoiding copying the string
    std::string_view view_input = input;
    if (view_input == "/save") {
      break;
    }

    if (input.length() != kSecretCodeLength) {
      std::cout << "Input must be exactly " << kSecretCodeLength
                << " digits long." << std::endl;
      continue;
    }

    bool valid = true;
    for (char c : input) {
      if (!isdigit(c) || c < '0' || c > '7') {
        std::cout << "Each digit must be between 0 and 7." << std::endl;
        valid = false;
        break;
      }
    }

    if (valid) {
      break;
    }
  }
  return input;
}
