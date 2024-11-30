/**
 * @file ui.h
 * @brief Declaration of all UI functions.
 */

#ifndef UI_H_
#define UI_H_

#include <string>
#include <vector>

#include <ncurses.h>

#define COLOR_MASTERMIND 8

/**
 * @brief Display the title banner.
 */
void Title(WINDOW *window);

/**
 * @brief Interpolates the color of the mastermind based on the player's life.
 *
 * @param life The player's life.
 * @param max_life The maximum life the player can have.
 */
void InterpolateColor(int life, int max_life);

/**
 * @brief Prompts user to press the enter key to continue the app.
 *
 * @param window The window to display the message.
 * @param y The y-coordinate of the message.
 */
void EnterToContinue(WINDOW *window, const int &y);

/**
 * @brief Prompts the player to select a choice from a given menu.
 *
 * @param window The window to display the selection.
 * @return int The player's selection.
 */
void UserChoice(WINDOW *window, int &highlight,
                const std::vector<std::string> &choices,
                const std::string &menu_title);

/**
 * @brief Print a menu.
 */
void PrintMenu(WINDOW *window, const int &highlight,
               const std::vector<std::string> &choices,
               const std::string &menu_title);

/**
 * @brief Print the header.
 *
 * @param window
 * @param y
 * @param header
 * @param longest_name_length
 */
void PrintHeader(WINDOW *window, int &y, const std::vector<std::string> &header,
                 const int &longest_name_length);

/**
 * @brief Print the instructions.
 */
void PrintInstructions(WINDOW *windo);

/**
 * @brief Print a horizontal line with color.
 *
 * @param window The window to print the line.
 * @param x The length of the line.
 */
void PrintHL(WINDOW *window);

/**
 * @brief Prints the player's guess and the feedback.
 *
 * @param window The window to display the secret code.
 * @param y The y-coordinate of the window.
 * @param x The x-coordinate of the window.
 * @param guess The player's guess.
 * @param feedback The feedback for the guess.
 */
void PrintGuess(WINDOW *window, int &y, int x, const std::vector<int> &guess,
                const std::string &feedback);

/**
 * @brief Prints the player's secret code.
 *
 * @param window The window to display the secret code.
 * @param y The y-coordinate of the window.
 * @param x The x-coordinate of the window.
 * @param code The player's secret code.
 */
void PrintCode(WINDOW *window, int &y, int x, std::vector<int> code);

/**
 * @brief Prints the summary of the game after the player has solved the
 * code.
 *
 * @param window The window to display the secret code.
 * @param y The y-coordinate of the window.
 * @param x The x-coordinate of the window.
 * @param guess The player's guess.
 * @param guesses_size The number of guesses the player made.
 * @param elapsed_time The time it took the player to solve the code.
 */
void PrintSolvedSummary(WINDOW *window, int &y, int x, const int &guesses_size,
                        const double &elapsed_time);

/**
 * @brief Update the highlight index.
 *
 * @tparam T The type of the elements in the choices vector.
 * @param highlight The current highlight index.
 * @param choices The vector of choices.
 * @param direction The direction to move the highlight.
 */
template <typename T>
void UpdateHighlight(int &highlight, const std::vector<T> &choices,
                     const int &direction) {
  highlight += direction;
  if (highlight < 0) {
    highlight = choices.size() - 1;
  } else if (highlight >= choices.size()) {
    highlight = 0;
  }
}

#endif // UI_H_
