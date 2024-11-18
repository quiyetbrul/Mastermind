/**
 * @file banner.cpp
 * @brief Declaration of all banner functions.
 */

#include <string>
#include <vector>

#include "ui/banner.h"

#include <ncurses.h>

void PrintBanner(WINDOW *window, int &y, int &x,
                 const std::vector<std::string> lines, const int &color_pair) {
  int longest_line = 0;
  for (const auto &line : lines) {
    if (line.length() > longest_line) {
      longest_line = line.length();
    }
  }
  wattron(window, COLOR_PAIR(color_pair));
  for (const auto &line : lines) {
    mvwprintw(window, ++y, x - (longest_line / 2), line.c_str());
  }
  wattroff(window, COLOR_PAIR(color_pair));
}

void Title(WINDOW *window) {
  wclear(window);
  wrefresh(window);
  // clang-format off
  std::vector<std::string> game_name={
  "_______ _______ _______ _______ _______  ______ _______ _____ __   _ ______ ",
  "|  |  | |_____| |______    |    |______ |_____/ |  |  |   |   | \\  | |     \\",
  "|  |  | |     | ______|    |    |______ |    \\_ |  |  | __|__ |  \\_| |_____/"};
  // clang-format on

  int y = 1;
  int x = getmaxx(window);
  x /= 2;
  std::string welcome_in_morse = ".-- . .-.. -.-. --- -- .    - --- ";
  mvwprintw(window, ++y, x - (welcome_in_morse.length() / 2),
            welcome_in_morse.c_str());

  init_pair(1, COLOR_CYAN, COLOR_BLACK);
  PrintBanner(window, y, x, game_name, 1);

  std::string by_in_rot13_morse =
      "--- .-..    -.. .... ...- .-.. .-. --.    --- . .... -.--";
  mvwprintw(window, ++y, x - (by_in_rot13_morse.length() / 2),
            by_in_rot13_morse.c_str());

  wrefresh(window);
}

void Congratulations(WINDOW *window, int &y) {
  // wclear(window);
  wrefresh(window);

  // clang-format off
  std::vector<std::string> congrats={
  "____ ____ _  _ ____ ____ ____ ___ ____",
  "|    |  | |\\ | | __ |__/ |__|  |  [__",
  "|___ |__| | \\| |__] |  \\ |  |  |  ___]"};
  // clang-format on

  int x = getmaxx(window);
  x /= 2;

  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  PrintBanner(window, y, x, congrats, 1);
  wrefresh(window);
}

void TryAgain(WINDOW *window) {
  wclear(window);
  wrefresh(window);

  // clang-format off
  std::vector<std::string> try_again={
  "___ ____ _   _    ____ ____ ____ _ _  _",
  " |  |__/  \\_/     |__| | __ |__| | |\\ |",
  " |  |  \\   |      |  | |__] |  | | | \\|",
  };
  // clang-format on

  int y = 1;
  int x = getmaxx(window);
  x /= 2;

  init_pair(1, COLOR_RED, COLOR_BLACK);
  PrintBanner(window, y, x, try_again, 1);
  wrefresh(window);
}

void Goodbye(WINDOW *window) {
  wclear(window);
  wrefresh(window);

  // clang-format off
  std::vector<std::string> goodbye={
  "____ ____ ____ ___  ___  _   _ ____",
  "| __ |  | |  | |  \\ |__]  \\_/  |___",
  "|__] |__| |__| |__/ |__]   |   |___",
  };
  // clang-format on

  int y = 1;
  int x = getmaxx(window);
  x /= 2;

  init_pair(1, COLOR_BLUE, COLOR_BLACK);
  PrintBanner(window, y, x, goodbye, 1);
  wrefresh(window);
}
