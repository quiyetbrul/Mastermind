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
void Title(WINDOW *win);
void Title();

/**
 * @brief Display the congratulations banner.
 */
void Congratulations();

/**
 * @brief Display the try again banner.
 */
void TryAgain();

/**
 * @brief Display the goodbye banner.
 */
void Goodbye();

#endif // UI_BANNER_H_
