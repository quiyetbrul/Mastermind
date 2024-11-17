/**
 * @file banner.cpp
 * @brief Declaration of all banner functions.
 */

#include <iostream>
#include <ncurses.h>
#include <string>
#include <vector>

#include "ui/banner.h"
#include "util/util.h"

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

  int y;
  int x;
  getmaxyx(window, y, x);
  y = 1;
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

// clang-format off
void Title() {
//   ClearScreen();
  // TODO: get terminal width dynamically
  std::cout << "                                      _ _ _ ____ _    ____ ____ _  _ ____     ___ ____\n";
  std::cout << "                                      | | | |___ |    |    |  | |\\/| |___      |  |  |\n";
  std::cout << "                                      |_|_| |___ |___ |___ |__| |  | |___      |  |__|\n\n";
  std::cout << ANSI_COLOR_YELLOW;
  std::cout << "███╗   ███╗ █████╗ ███████╗████████╗███████╗██████╗ ███╗   ███╗██╗███╗   ██╗██████╗       ██████╗  █████╗ ███╗   ███╗███████╗\n";
  std::cout << "████╗ ████║██╔══██╗██╔════╝╚══██╔══╝██╔════╝██╔══██╗████╗ ████║██║████╗  ██║██╔══██╗     ██╔════╝ ██╔══██╗████╗ ████║██╔════╝\n";
  std::cout << "██╔████╔██║███████║███████╗   ██║   █████╗  ██████╔╝██╔████╔██║██║██╔██╗ ██║██║  ██║     ██║  ███╗███████║██╔████╔██║█████╗\n";
  std::cout << "██║╚██╔╝██║██╔══██║╚════██║   ██║   ██╔══╝  ██╔══██╗██║╚██╔╝██║██║██║╚██╗██║██║  ██║     ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝\n";
  std::cout << "██║ ╚═╝ ██║██║  ██║███████║   ██║   ███████╗██║  ██║██║ ╚═╝ ██║██║██║ ╚████║██████╔╝     ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗\n";
  std::cout << "╚═╝     ╚═╝╚═╝  ╚═╝╚══════╝   ╚═╝   ╚══════╝╚═╝  ╚═╝╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═════╝       ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝\n";
  std::cout << ANSI_RESET;
  std::cout << "                                ___  _   _    ____ _  _ _ _   _ ____ ___    ___  ____ _  _ _\n";
  std::cout << "                                |__]  \\_/     |  | |  | |  \\_/  |___  |     |__] |__/ |  | |\n";
  std::cout << "                                |__]   |      |_\\| |__| |   |   |___  |     |__] |  \\ |__| |___\n\n";
}

void Congratulations() {
  std::cout << ANSI_COLOR_GREEN << ANSI_BLINK;
  std::cout << " ██████╗ ██████╗ ███╗   ██╗ ██████╗ ██████╗  █████╗ ████████╗██╗   ██╗██╗      █████╗ ████████╗██╗ ██████╗ ███╗   ██╗███████╗\n";
  std::cout << "██╔════╝██╔═══██╗████╗  ██║██╔════╝ ██╔══██╗██╔══██╗╚══██╔══╝██║   ██║██║     ██╔══██╗╚══██╔══╝██║██╔═══██╗████╗  ██║██╔════╝\n";
  std::cout << "██║     ██║   ██║██╔██╗ ██║██║  ███╗██████╔╝███████║   ██║   ██║   ██║██║     ███████║   ██║   ██║██║   ██║██╔██╗ ██║███████╗\n";
  std::cout << "██║     ██║   ██║██║╚██╗██║██║   ██║██╔══██╗██╔══██║   ██║   ██║   ██║██║     ██╔══██║   ██║   ██║██║   ██║██║╚██╗██║╚════██║\n";
  std::cout << "╚██████╗╚██████╔╝██║ ╚████║╚██████╔╝██║  ██║██║  ██║   ██║   ╚██████╔╝███████╗██║  ██║   ██║   ██║╚██████╔╝██║ ╚████║███████║\n";
  std::cout << " ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝    ╚═════╝ ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝\n";
  std::cout << ANSI_RESET;
}

void Congratulations(WINDOW* window, int &y){
  // wclear(window);
  wrefresh(window);

  // clang-format off
  std::vector<std::string> congrats={
  "____ ____ _  _ ____ ____ ____ ___ ____",
  "|    |  | |\\ | | __ |__/ |__|  |  [__",
  "|___ |__| | \\| |__] |  \\ |  |  |  ___]"};
  // clang-format on

  int _;
  int x;
  getmaxyx(window, _, x);
  x /= 2;

  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  PrintBanner(window, y, x, congrats, 1);
  wrefresh(window);
}
// clang-format off

void TryAgain() {
  std::cout << ANSI_COLOR_RED;
  std::cout << "                            ████████╗██████╗ ██╗   ██╗      █████╗  ██████╗  █████╗ ██╗███╗   ██╗\n";
  std::cout << "                            ╚══██╔══╝██╔══██╗╚██╗ ██╔╝     ██╔══██╗██╔════╝ ██╔══██╗██║████╗  ██║\n";
  std::cout << "                               ██║   ██████╔╝ ╚████╔╝      ███████║██║  ███╗███████║██║██╔██╗ ██║\n";
  std::cout << "                               ██║   ██╔══██╗  ╚██╔╝       ██╔══██║██║   ██║██╔══██║██║██║╚██╗██║\n";
  std::cout << "                               ██║   ██║  ██║   ██║        ██║  ██║╚██████╔╝██║  ██║██║██║ ╚████║\n";
  std::cout << "                               ╚═╝   ╚═╝  ╚═╝   ╚═╝        ╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝\n\n";
  std::cout << ANSI_RESET;
}

void TryAgain(WINDOW* window){
  wclear(window);
  wrefresh(window);

  // clang-format off
  std::vector<std::string> try_again={
  "___ ____ _   _    ____ ____ ____ _ _  _",
  " |  |__/  \\_/     |__| | __ |__| | |\\ |",
  " |  |  \\   |      |  | |__] |  | | | \\|",
  };
  // clang-format on

  int y;
  int x;
  getmaxyx(window, y, x);
  y = 1;
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

  int y;
  int x;
  getmaxyx(window, y, x);
  y = 1;
  x /= 2;

  init_pair(1, COLOR_BLUE, COLOR_BLACK);
  PrintBanner(window, y, x, goodbye, 1);
  wrefresh(window);
}

// clang-format off
void Goodbye() {
  ClearScreen();
  std::cout << ANSI_COLOR_BLUE;
  std::cout << "                                    ██████╗  ██████╗  ██████╗ ██████╗ ██████╗ ██╗   ██╗███████╗\n";
  std::cout << "                                   ██╔════╝ ██╔═══██╗██╔═══██╗██╔══██╗██╔══██╗╚██╗ ██╔╝██╔════╝\n";
  std::cout << "                                   ██║  ███╗██║   ██║██║   ██║██║  ██║██████╔╝ ╚████╔╝ █████╗\n";
  std::cout << "                                   ██║   ██║██║   ██║██║   ██║██║  ██║██╔══██╗  ╚██╔╝  ██╔══╝\n";
  std::cout << "                                   ╚██████╔╝╚██████╔╝╚██████╔╝██████╔╝██████╔╝   ██║   ███████╗\n";
  std::cout << "                                    ╚═════╝  ╚═════╝  ╚═════╝ ╚═════╝ ╚═════╝    ╚═╝   ╚══════╝\n\n";
  std::cout << ANSI_RESET;
}
