/**
 * @file util.cpp
 * @brief Declaration of all game-wide utilities.
 */

#ifndef UTIL_UTIL_H_
#define UTIL_UTIL_H_

#include <functional>
#include <iostream>
#include <limits>
#include <string>

// TODO: move to definitions file

const int kTerminalWidth = 125;
const int kTerminalHeight = 24;

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_RESET "\x1b[0m"
#define ANSI_BLINK "\x1b[5m"
#define DELETE_LINE "\033[A\033[K"

/**
 * @brief Clear the terminal screen.
 *
 * This function clears the terminal screen.
 */
void ClearScreen();

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
 * @brief Generate a random number between min and max.
 *
 * This function generates a random number between the specified minimum and
 * maximum values using mt19937.
 *
 * @param min The minimum value of the random number.
 * @param max The maximum value of the random number.
 * @return int The generated random number.
 */
int RandomNumber(const int &min, const int &max);

// TODO: think where this should be. UI maybe? it deals with menus
/**
 * @brief Return to a specific function.
 *
 * This function prompts the user to press the enter key to return to a specific
 * function.
 *
 * @param where The name of the function to return to.
 * @param function The function to return to.
 */
inline void ReturnTo(const std::string &where,
                     const std::function<void()> &function) {
  std::cout << "Press enter key to return to " << where << std::endl;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cin.get();
  std::cin.clear();
  function();
}

/**
 * @brief Get string input from user.
 *
 * This function prompts the user for a string input and validates it.
 * If the input is invalid, the user is prompted to enter a valid input.
 *
 * @param prompt The prompt message to display to the user.
 * @return std::string The validated string input.
 */
std::string InputString(const std::string &prompt);

/**
 * @brief Get integer input from user.
 *
 * This function prompts the user for an integer input and validates it.
 * If the input is invalid, the user is prompted to enter a valid input.
 *
 * @param prompt The prompt message to display to the user.
 * @param start_range The minimum value of the input range.
 * @param end_range The maximum value of the input range.
 * @return int The validated integer input.
 */
int InputInteger(const std::string prompt, const int &start_range,
                 const int &end_range);

/**
 * @brief Get character input from user.
 *
 * This function prompts the user for a character input and validates it.
 * If the input is invalid, the user is prompted to enter a valid input.
 *
 * @param prompt The prompt message to display to the user.
 * @param yes The character representing "yes".
 * @param no The character representing "no".
 * @return char The validated character input.
 */
char InputChar(const std::string &prompt, const char &yes, const char &no);

#endif // UTIL_UTIL_H_
