/**
 * @file util.cpp
 * @brief Implementation for utility functions used by the player.
 */

#include "util.h"

#include <algorithm>
#include <iomanip>
#include <sstream>

#include "logger/logger.h"
#include "util/util.h"

namespace player {

#define COLOR_MASTERMIND 8

std::string InputSecretCode(WINDOW *window, int &y, int x, std::string prompt,
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

  // Second pass: check for white pegs (correct digit, wrong position)
  for (int i = 0; i < secret_code_length; ++i) {
    if (!code_used[i]) { // Only consider unused code positions
      for (int j = 0; j < secret_code_length; ++j) {
        if (!guess_used[j] &&
            code[i] == guess[j]) { // Find unused matching digit
          result.append("W");
          guess_used[j] = true; // Mark this guess position as used
          break;
        }
      }
    }
  }

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

std::vector<int> StringToVector(std::string input) {
  std::vector<int> result(input.begin(), input.end());
  std::transform(result.begin(), result.end(), result.begin(),
                 [](char c) { return c - '0'; });

  return result;
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
} // namespace player
