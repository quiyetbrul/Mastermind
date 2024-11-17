/**
 * @file menu.cpp
 * @brief Implementation of all Menu functions.
 */

#include "menu.h"

#include "util/util.h"

void PrintMenu(WINDOW *menu_win, const int &highlight,
               const std::vector<std::string> &choices) {
  int x, y;
  getmaxyx(menu_win, y, x);
  y = 0;
  x /= 2;
  for (int i = 0; i < choices.size(); ++i) {
    if (highlight == i) {
      wattron(menu_win, A_STANDOUT);
      mvwprintw(menu_win, y, x - (choices[i].length() / 2), "%s",
                choices[i].c_str());
      wattroff(menu_win, A_STANDOUT);
    } else {
      mvwprintw(menu_win, y, x - (choices[i].length() / 2), "%s",
                choices[i].c_str());
    }
    ++y;
  }
  wrefresh(menu_win);
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
