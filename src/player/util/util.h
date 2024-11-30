/**
 * @file util.h
 * @brief Declarations for utility functions used by the player.
 */

#ifndef PLAYER_UTIL_UTIL_H_
#define PLAYER_UTIL_UTIL_H_

#include <string>
#include <vector>

#include <ncurses.h>

namespace player {

#define COLOR_MASTERMIND 8

/**
 * @brief Generates feedback for a guess based on the secret code.
 *
 * @param guess The guess to be evaluated.
 * @param code The secret code to compare the guess against.
 * @param secret_code_length The length of the secret code.
 * @return std::string A string containing the feedback for the guess.
 */
std::string GiveFeedback(const std::vector<int> &guess,
                         const std::vector<int> &code,
                         const int &secret_code_length);

/**
 * @brief Generates a hint for the player based on the guess and the secret
 * code.
 *
 * This will only say if the guess[i] is higher or lower than the code[i].
 * Otherwise, it's basically giving the answer if it also hints at switching the
 * position.
 *
 * @param guess The player's guess.
 * @param code The secret code.
 * @return std::string The hint based on the player's guess and the secret code.
 */
std::string GiveHint(const std::vector<int> &guess,
                     const std::vector<int> &code);

/**
 * @brief Interpolates the color of the mastermind based on the player's life.
 *
 * @param life The player's life.
 * @param max_life The maximum life the player can have.
 */
void InterpolateColor(int life, int max_life);

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
} // namespace player
#endif // PLAYER_UTIL_UTIL_H_
