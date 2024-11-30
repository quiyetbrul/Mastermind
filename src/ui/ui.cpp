/**
 * @file ui.cpp
 * @brief Implementation of all UI functions.
 */

#include "ui.h"

#include <iomanip>
#include <sstream>

#include "logger/logger.h"

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
    mvwprintw(window, ++y, x - (longest_line / 2), "%s", line.c_str());
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
  mvwprintw(window, ++y, x - (welcome_in_morse.length() / 2), "%s",
            welcome_in_morse.c_str());

  init_pair(1, COLOR_CYAN, COLOR_BLACK);
  PrintBanner(window, y, x, game_name, 1);

  std::string by_in_rot13_morse =
      "--- .-..    -.. .... ...- .-.. .-. --.    --- . .... -.--";
  mvwprintw(window, ++y, x - (by_in_rot13_morse.length() / 2), "%s",
            by_in_rot13_morse.c_str());

  wrefresh(window);
}

void InterpolateColor(int life, int max_life) {
  // RGB values for cyan and red
  int cyan_r = 0, cyan_g = 1000, cyan_b = 1000;
  int red_r = 1000, red_g = 0, red_b = 0;

  // Calculate the interpolation factor (0.0 to 1.0)
  float factor = static_cast<float>(max_life - life) / max_life;

  // Interpolate RGB values
  int r = static_cast<int>(cyan_r + factor * (red_r - cyan_r));
  int g = static_cast<int>(cyan_g + factor * (red_g - cyan_g));
  int b = static_cast<int>(cyan_b + factor * (red_b - cyan_b));

  // Avoid shades of gray
  if (r == g && g == b) {
    if (r > 500) {
      r -= 100;
    } else {
      r += 100;
    }
  }

  // Update the color in ncurses
  init_color(COLOR_MASTERMIND, r, g, b);
  init_pair(1, COLOR_MASTERMIND, COLOR_BLACK);
}

void EnterToContinue(WINDOW *window, const int &y) {
  int x = getmaxx(window);
  x /= 2;

  std::string press_enter = "Press enter to continue...";
  mvwprintw(window, y, x - (press_enter.length() / 2), "%s",
            press_enter.c_str());

  int c = wgetch(window);
  while (c != '\n') {
    c = wgetch(window);
  }

  wclear(window);
}

void UserChoice(WINDOW *window, int &highlight,
                const std::vector<std::string> &choices,
                const std::string &menu_title) {
  int choice = 0;

  bool loop = true;
  while (loop) {
    wclear(window);
    wrefresh(window);
    PrintMenu(window, highlight, choices, menu_title);
    choice = wgetch(window);
    switch (choice) {
    case KEY_UP:
      UpdateHighlight(highlight, choices, -1);
      break;
    case KEY_DOWN:
      UpdateHighlight(highlight, choices, 1);
      break;
    case 10:
      wclear(window);
      wrefresh(window);
      loop = false;
    }
  }
}

void PrintHeader(WINDOW *window, int &y, const std::vector<std::string> &header,
                 const int &longest_name_length) {
  int x = getmaxx(window);
  x /= 2;
  int temp = x;
  int col_width = longest_name_length + x;
  int total_width = header.size() * longest_name_length;
  for (const auto &head : header) {
    temp += col_width;
    mvwprintw(window, y, (temp / 4) + total_width, "%s", head.c_str());
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
  PrintHL(window);
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
  PrintHL(window);
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
    mvwprintw(window, y++, x - (instruction.length() / 2), "%s",
              instruction.c_str());
  }
  EnterToContinue(window, y);
  return;
}

void PrintHL(WINDOW *window) {
  wattron(window, COLOR_PAIR(2));
  mvwhline(window, 0, 0, 0, getmaxx(window));
  wattroff(window, COLOR_PAIR(2));
}

void PrintGuess(WINDOW *window, int &y, int x, const std::vector<int> &guess,
                const std::string &feedback) {
  int total_width_needed = guess.size();
  // space between guess digits
  total_width_needed += (2 * guess.size());
  // space between guess and feedback + feedback max length
  total_width_needed += (4 + guess.size());
  // center the guess and feedback
  total_width_needed /= 2;
  x -= total_width_needed; // "1  2  3  4    BBBB"
  for (const auto &i : guess) {
    mvwprintw(window, y, x, "%d", i);
    x += 2;
  }
  mvwprintw(window, y++, x + 4, "%s", feedback.c_str());
  wrefresh(window);
}

void PrintCode(WINDOW *window, int &y, int x, std::vector<int> code) {
  for (const auto &i : code) {
    mvwprintw(window, y, x - 4, "%d ", i);
    x += 2;
  }
  y++;
  wrefresh(window);
}

void PrintSolvedSummary(WINDOW *window, int &y, int x, const int &guesses_size,
                        const double &elapsed_time) {
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(3) << elapsed_time;
  std::string summary = "Solved in " + std::to_string(guesses_size) +
                        (guesses_size == 1 ? " guess" : " guesses") + " and " +
                        oss.str() + " seconds.";
  Logger &logger = Logger::GetInstance();
  logger.Log(summary);
  mvwprintw(window, y++, x - (summary.length() / 2), "%s", summary.c_str());
  wrefresh(window);
}
