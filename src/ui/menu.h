/**
 * @file menu.h
 * @brief Declaration of all Menu functions.
 */

#ifndef UI_MENU_H_
#define UI_MENU_H_

#include <string>
#include <vector>

#include <ncurses.h>

void print_menu(WINDOW *window, int y, int x, int highlight,
                const std::vector<std::string> &choices);

/**
 * @brief Print the main menu.
 */
void PrintMenu();

/**
 * @brief Print the player menu.
 */
void PrintPlayerMenu();

/**
 * @brief Print the instructions.
 */
void PrintInstructions(WINDOW *window, int y, int x);

#endif // UI_MENU_H_
