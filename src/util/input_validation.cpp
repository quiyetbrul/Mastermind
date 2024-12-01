/**
 * @file input_validation.cpp
 * @brief Implementation of input validation functions.
 */

#include "util.h"

#include <string>

std::string InputString(WINDOW *window, int y, std::string prompt) {
  int x = getmaxx(window);
  x /= 2;
  std::string input;

  while (true) {
    mvwprintw(window, y, x - (prompt.length() / 2) - 10, "%s", prompt.c_str());
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
    prompt = "Input cannot be empty. " + prompt;
  }

  wmove(window, y, 0);
  wclrtoeol(window);

  return input;
}

std::string InputSecretCode(WINDOW *window, int &y, const int &x,
                            std::string prompt, const int &secret_code_length,
                            const int &secret_code_min_digit,
                            const int &secret_code_max_digit,
                            const bool &is_human_player) {
  std::string input;

  while (true) {
    wrefresh(window);

    wmove(window, y + 1, x - 2);
    input = InputString(window, y, prompt);

    if (is_human_player && (input == "s" || input == "h" || input == "e")) {
      return input;
    }

    if (input.length() != secret_code_length) {
      prompt = "Input must be exactly " + std::to_string(secret_code_length) +
               " digits long.";
      continue;
    }

    if (!std::all_of(input.begin(), input.end(),
                     [secret_code_min_digit, secret_code_max_digit](char c) {
                       return c >= '0' + secret_code_min_digit &&
                              c <= '0' + secret_code_max_digit;
                     })) {
      prompt = "Each digit must be between " +
               std::to_string(secret_code_min_digit) + " and " +
               std::to_string(secret_code_max_digit) + ".";
      continue;
    }

    break;
  }

  std::vector<int> result(input.begin(), input.end());
  std::transform(result.begin(), result.end(), result.begin(),
                 [](char c) { return c - '0'; });

  return input;
}
