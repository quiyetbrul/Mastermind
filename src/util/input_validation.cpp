/**
 * @file input_validation.cpp
 * @brief Implementation of input validation functions.
 */

#include "util.h"

#include <string>

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
