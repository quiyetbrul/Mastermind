/**
 * @file util.h
 * @brief Declaration of all game-wide utilities.
 */

#ifndef UTIL_UTIL_H_
#define UTIL_UTIL_H_

#include <string>
#include <vector>

#include <ncurses.h>

const int kTerminalWidth = 100;
const int kTerminalHeight = 30;

/**
 * @brief Close the terminal.
 *
 * This function closes the terminal.
 */
void CloseTerminal();

/**
 * @brief Set the terminal size.
 *
 * This function sets the terminal size to the specified width and height.
 * Currently, it is set to the default values of 125x24.
 *
 * @param width The width of the terminal.
 * @param height The height of the terminal.
 */
void SetTerminalSize(const int &width, const int &height);

/**
 * @brief Set the terminal title.
 *
 * This function sets the terminal title to the specified title.
 *
 * @param title The title to set.
 */
void SetTerminalTitle(const std::string &title);

/**
 * @brief Generate random numbers using Random.org API.
 *
 * This function generates random numbers between the minimum and the maximum
 * values n-times using the Random.org API.
 * FOLLOWED EXAMPLE FROM https://terminalroot.com/using-curl-with-cpp/
 *
 * @param generate The number of random numbers to generate.
 * @param min The minimum value of the random number.
 * @param max The maximum value of the random number.
 * @return std::vector<int> The generated random numbers.
 */
std::vector<int> GenRandom(const int &generate, const int &min, const int &max);

/**
 * @brief Get string input from user.
 *
 * This function prompts the user for a string input and validates it.
 * A valid string input is a non-empty string.
 *
 * @param window The window to display the prompt.
 * @param y The y-coordinate of the prompt.
 * @param prompt The prompt message to display to the user.
 * @return std::string The validated string input.
 */
std::string InputString(WINDOW *window, int y, std::string prompt);

/**
 * @brief Prompts the player to input a guess.
 *
 * @param window The window to display the prompt.
 * @param prompt The prompt to display to the player.
 * @param secret_code_length The length of the secret code.
 * @param secret_code_min_digit The minimum digit allowed in the secret
 * code.
 * @param secret_code_max_digit The maximum digit allowed in the secret
 * code.
 * @return std::vector<int> A vector containing the player's guess.
 */
std::string InputSecretCode(WINDOW *window, int &y, int x, std::string prompt,
                            const int &secret_code_length,
                            const int &secret_code_min_digit,
                            const int &secret_code_max_digit,
                            const bool &is_single = false);

/**
 * @brief Converts a string to a vector of integers.
 *
 * @param input The string to convert.
 * @return std::vector<int> The vector of integers.
 */
inline std::vector<int> StringToVector(std::string input) {
  std::vector<int> result(input.begin(), input.end());
  std::transform(result.begin(), result.end(), result.begin(),
                 [](char c) { return c - '0'; });

  return result;
}

#endif // UTIL_UTIL_H_
