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
               const std::vector<std::string> &choices);

/**
 * @brief Print the instructions.
 */
void PrintInstructions(WINDOW *windo);

#endif // UI_MENU_H_
