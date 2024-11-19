/**
 * @file util.cpp
 * @brief Implementation for utility functions used by the player.
 */

#include "util.h"

#include <algorithm>

#include "ui/menu.h"
#include "util/util.h"

namespace player {
std::string InputGuess(WINDOW *window, int &y, int x, std::string prompt,
                       const int &secret_code_length,
                       const int &secret_code_min_digit,
                       const int &secret_code_max_digit,
                       const bool &is_single) {
  std::string input;

  while (true) {
    wrefresh(window);

    wmove(window, y + 1, x - 2);
    input = InputString(window, y, prompt);

    if (is_single && (input == "s" || input == "h" || input == "e")) {
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

std::vector<int> ConvertToVector(std::string input) {
  std::vector<int> result(input.begin(), input.end());
  std::transform(result.begin(), result.end(), result.begin(),
                 [](char c) { return c - '0'; });

  return result;
}

std::string GiveHint(const std::vector<int> &guess,
                     const std::vector<int> &code) {
  std::string hint;

  for (int i = 0; i < guess.size(); i++) {
    if (guess[i] != code[i]) {
      hint = "Position " + std::to_string(i + 1) + " needs to be " +
             (guess[i] > code[i] ? "lower" : "higher");
      break;
    }
  }

  return hint;
}

void PrintSolvedSummary(WINDOW *window, int &y, int x, const int &guesses_size,
                        const double &elapsed_time) {
  std::string summary = "Solved in " + std::to_string(guesses_size) +
                        " guess(es) and " + std::to_string(elapsed_time) +
                        " seconds.";
  mvwprintw(window, y++, x - (summary.length() / 2), "%s", summary.c_str());
  wrefresh(window);
}

std::string GiveFeedback(const std::vector<int> &guess,
                         const std::vector<int> &code,
                         const int &secret_code_length) {
  std::string result;
  std::vector<bool> guess_used(secret_code_length, false);
  std::vector<bool> code_used(secret_code_length, false);

  // First pass: check for black pegs (exact matches)
  for (int i = 0; i < secret_code_length; ++i) {
    if (guess[i] == code[i]) {
      result.append("B");
      guess_used[i] = true; // Mark this guess position as used
      code_used[i] = true;  // Mark this code position as used
    }
  }

  // Second pass: check for white pegs (correct color, wrong position)
  for (int i = 0; i < secret_code_length; ++i) {
    if (!code_used[i]) { // Only consider unused code positions
      for (int j = 0; j < secret_code_length; ++j) {
        if (!guess_used[j] &&
            code[i] == guess[j]) { // Find unused matching color
          result.append("W");
          guess_used[j] = true; // Mark this guess position as used
          break;
        }
      }
    }
  }

  return result;
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

int InputDifficulty(WINDOW *window) {
  std::vector<std::string> difficulty_options = {"Easy", "Medium", "Hard",
                                                 "Back"};
  int choice = 0;
  int highlight = 0;

  bool loop = true;
  while (loop) {
    wclear(window);
    wrefresh(window);
    PrintMenu(window, highlight, difficulty_options, "Select Difficulty");
    choice = wgetch(window);
    switch (choice) {
    case KEY_UP:
      UpdateHighlight(highlight, difficulty_options, -1);
      break;
    case KEY_DOWN:
      UpdateHighlight(highlight, difficulty_options, 1);
      break;
    case 10:
      wclear(window);
      wrefresh(window);
      loop = false;
    }
  }
  return highlight;
}
} // namespace player
