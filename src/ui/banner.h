/**
 * @file banner.h
 * @brief Declaration of all banner functions.
 */

#ifndef UI_BANNER_H_
#define UI_BANNER_H_

#include <ncurses.h>

// TODO: i probably don't need the other banners. just change colors

/**
 * @brief Display the title banner.
 */
void Title(WINDOW *window);

/**
 * @brief Display the congratulations banner.
 */
void Congratulations(WINDOW *window, int &y);

/**
 * @brief Display the try again banner.
 */
void TryAgain(WINDOW *window);

/**
 * @brief Display the goodbye banner.
 */
void Goodbye(WINDOW *window);

#endif // UI_BANNER_H_
