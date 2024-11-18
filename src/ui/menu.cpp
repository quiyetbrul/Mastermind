/**
 * @file menu.cpp
 * @brief Implementation of all Menu functions.
 */

#include "menu.h"

#include "util/util.h"

void PrintHeader(WINDOW* window, int & y, const std::vector<std::string>& header, const int& longest_name_length) {
  int _;
  int x;
  getmaxyx(window, _, x);
  x /= 2;
  int temp = x;
  int col_width = longest_name_length + x;
  int total_width = header.size() * longest_name_length;
  for (const auto &head : header) {
    temp += col_width;
    mvwprintw(window, y, (temp / 4) + total_width, head.c_str());
  }
  ++y;
  wrefresh(window);
}

void PrintMenu(WINDOW *window, const int &highlight,
               const std::vector<std::string> &choices) {
  int x, y;
  getmaxyx(window, y, x);
  y = 2;
  x /= 2;
  for (int i = 0; i < choices.size(); ++i) {
    if (highlight == i) {
      wattron(window, A_STANDOUT);
      mvwprintw(window, y, x - (choices[i].length() / 2), "%s",
                choices[i].c_str());
      wattroff(window, A_STANDOUT);
    } else {
      mvwprintw(window, y, x - (choices[i].length() / 2), "%s",
                choices[i].c_str());
    }
    ++y;
  }
  wrefresh(window);
}

void PrintInstructions(WINDOW *window) {
  int y;
  int x;
  getmaxyx(window, y, x);
  y = 1;
  wclear(window);
  std::string instructions[] = {
      "Instructions:",
      "The secret code length and each digit range depend on the difficulty.",
      "The settings are displayed at the top of the screen in the following format: ",
      "[difficulty] [code length] [min digit] [max digit]",
      "If you are Codebreaker, crack the secret code.",
      "If you are Codemaster, create a secret code for the AI to crack.",
      "Each feedback character represents a digit in the secret code:",
      "- 'B' represents a correct digit in the correct position",
      "- 'W' represents a correct digit in the wrong position",
      "You have 10 chances to guess the secret code, and you have 3 [h]ints.",
      "You may [s]ave or [e]xit the game at any time.",
      "Good Luck!"};

  for (const auto &instruction : instructions) {
    mvwprintw(window, y++, (x / 2) - (instruction.length() / 2),
              instruction.c_str());
  }
  EnterToContinue(window, y);
  return;
}
