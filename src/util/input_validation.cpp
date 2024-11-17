/**
 * @file input_validation.cpp
 * @brief Implementation of input validation functions.
 */

#include "util.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>
#include <string>

// TODO: get string input, validate, and convert to integer
// rename GetIntegerInput
// TODO: delete prev line if input is invalid
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

std::string InputString(const std::string &prompt) {
  std::string input;
  while (true) {
    std::cout << prompt;
    std::cin >> input;

    // Check if all characters are alphabetic
    if (std::all_of(input.begin(), input.end(),
                    [](char c) { return std::isalpha(c); })) {
      break;
    } else {
      std::cout << "Invalid input. Please enter only alphabets." << std::endl;
    }
  }
  return input;
}

std::string InputString(WINDOW *window, int y, const std::string &prompt) {
  int _;
  int x;
  getmaxyx(window, _, x);
  x /= 2;
  std::string input;

  while (true) {
    mvwprintw(window, y, x - (prompt.length() / 2) - 10, prompt.c_str());
    wmove(window, y, x - (prompt.length() / 2) - 10 + prompt.length() + 1);
    wrefresh(window);

    echo();
    curs_set(1);
    char buffer[256];
    wgetnstr(window, buffer, sizeof(buffer) - 1);
    input = std::string(buffer);
    curs_set(0);
    noecho();

    if (!input.empty()) {
      break;
    }

    wmove(window, y, 0);
    wclrtoeol(window);
    mvwprintw(window, y, x - (prompt.length() / 2) - 10,
              "Input cannot be empty. ");
  }

  wmove(window, y, 0);
  wclrtobot(window);

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
