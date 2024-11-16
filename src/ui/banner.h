/**
 * @file banner.h
 * @brief Declaration of all banner functions.
 */

#ifndef UI_BANNER_H_
#define UI_BANNER_H_

#include <ncurses.h>

/**
 * @brief Display the title banner.
 */
void Title(WINDOW *window);
void Title();

/**
 * @brief Display the congratulations banner.
 */
void Congratulations();
void Congratulations(WINDOW *window);

/**
 * @brief Display the try again banner.
 */
void TryAgain();
void TryAgain(WINDOW *window);

/**
 * @brief Display the goodbye banner.
 */
void Goodbye();
void Goodbye(WINDOW *window);

#endif // UI_BANNER_H_
