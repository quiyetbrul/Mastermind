#include "util.h"

#include <iostream>

int InputInteger(const std::string prompt, const int &start_range,
                 const int &end_range) {
  int input;
  do {
    std::cout << prompt;
    try {
      std::cin >> input;
      if (std::cin.fail() || input < start_range || input > end_range) {
        std::cin.clear(); // clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                        '\n'); // discard invalid input
        std::cout << "Invalid input. Please enter a valid input between "
                  << start_range << " and " << end_range << std::endl;
      } else
        break;
    } catch (std::invalid_argument &e) {
      std::cout << e.what() << std::endl;
    }
  } while (true);
  return input;
}

char InputChar(const std::string &prompt, const char &yes, const char &no) {
  char input;
  do {
    std::cout << prompt;
    try {
      std::cin >> input;
      input = tolower(input);
      if (std::cin.fail() || (input != yes && input != no)) {
        std::cin.clear(); // clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                        '\n'); // discard invalid input
        std::cout << "Invalid input. Please enter a valid input between " << yes
                  << " and " << no << std::endl;
      } else
        break;
    } catch (std::invalid_argument &e) {
      std::cout << e.what() << std::endl;
    }
  } while (true);
  return input;
}

std::string InputGuess(const std::string &prompt) {
  std::string input;
  while (true) {
    std::cout << prompt;
    std::cin >> input;

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
