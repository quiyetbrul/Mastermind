/**
 * @file menu.h
 * @brief Declaration of all Menu functions.
 */

#ifndef UI_MENU_H_
#define UI_MENU_H_

#include <string>
#include <vector>

#include <ncurses.h>

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
 * @brief Prompts user to press the enter key to continue the app.
 *
 * @param window The window to display the message.
 * @param y The y-coordinate of the message.
 */
void EnterToContinue(WINDOW *window, const int &y);

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

/**
 * @brief Print a horizontal line with color.
 *
 * @param window The window to print the line.
 * @param x The length of the line.
 */
void PrintHL(WINDOW *window);

#endif // UI_MENU_H_
