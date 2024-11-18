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

#endif // UI_MENU_H_
