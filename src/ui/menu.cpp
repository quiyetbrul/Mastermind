/**
 * @file menu.cpp
 * @brief Implementation of all Menu functions.
 */

#include "menu.h"

#include <iostream>
#include <ncurses.h>

#include "ui/banner.h"

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

void PrintPlayerMenu() {
  Title();
  std::cout << "1. Quick game\n";
  std::cout << "2. Codemaster\n";
  std::cout << "3. Back\n";
}

void PrintInstructions(WINDOW *window, int y, int x) {
  wclear(window);
  mvwprintw(window, y++, x, "Instructions:");
  mvwprintw(
      window, y++, x,
      "Depending on the difficulty level, the length of the secret code ");
  mvwprintw(window, y++, x, "and the range of each digit vary.");
  mvwprintw(window, y++, x,
            "If you are the codebreaker, you have to guess the secret code. If "
            "you are");
  mvwprintw(window, y++, x,
            "the codemaster, you have to create a secret code that the AI "
            "codebreaker has to guess.");
  mvwprintw(window, y++, x,
            "Each feedback character represents a digit in the secret code:");
  mvwprintw(window, y++, x,
            "- 'B' represents a correct digit in the correct position");
  mvwprintw(window, y++, x,
            "- 'W' represents a correct digit in the wrong position");
  mvwprintw(window, y++, x,
            "You have 10 chances to guess the secret code. You may save or "
            "exit the game at any time.");
  mvwprintw(window, y++, x, "Good Luck!");
  mvwprintw(window, y++, x, "Press enter to continue...");
  int c = wgetch(window);
  while (c != '\n') {
    c = wgetch(window);
  }
  wclear(window);
  wrefresh(window);
}
