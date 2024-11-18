/**
 * @file menu.cpp
 * @brief Implementation of all Menu functions.
 */

#include "menu.h"

void PrintHeader(WINDOW *window, int &y, const std::vector<std::string> &header,
                 const int &longest_name_length) {
  int x = getmaxx(window);
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
               const std::vector<std::string> &choices,
               const std::string &menu_title) {
  wclear(window);

  int y = 0;
  int x = getmaxx(window);
  PrintHL(window, x);
  x /= 2;

  mvwprintw(window, y++, x - (menu_title.size() / 2), "%s", menu_title.c_str());

  // y = 2;
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
  wclear(window);
  int y = 0;
  int x = getmaxx(window);
  PrintHL(window, x);
  x /= 2;

  // clang-format off
  std::string instructions[] = {
      "Instructions",
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
  // clang-format on

  for (const auto &instruction : instructions) {
    mvwprintw(window, y++, x - (instruction.length() / 2), instruction.c_str());
  }
  EnterToContinue(window, y);
  return;
}

void EnterToContinue(WINDOW *window, const int &y) {
  int x = getmaxx(window);
  x /= 2;

  std::string press_enter = "Press enter to continue...";
  mvwprintw(window, y, x - (press_enter.length() / 2), press_enter.c_str());

  int c = wgetch(window);
  while (c != '\n') {
    c = wgetch(window);
  }

  wclear(window);
}

void PrintHL(WINDOW *window, const int &x) {
  init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
  wattron(window, COLOR_PAIR(2));
  mvwhline(window, 0, 0, 0, x);
  wattroff(window, COLOR_PAIR(2));
}
