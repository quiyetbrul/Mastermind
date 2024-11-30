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

#endif // UTIL_UTIL_H_
