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
 * @brief Prints the summary of the game after the player has solved the code.
 *
 * @param guess
 * @param guesses_size
 * @param elapsed_time
 */
void PrintSolvedSummary(const std::vector<int> secret_code,
                        const int &guesses_size, const double &elapsed_time);
void PrintSolvedSummary(WINDOW *window, int &y, int x, const int &guesses_size,
                        const double &elapsed_time);

/**
 * @brief Prompts the player to input a guess.
 *
 * @param window The window to display the prompt.
 * @param prompt The prompt to display to the player.
 * @param secret_code_length The length of the secret code.
 * @param secret_code_min_digit The minimum digit allowed in the secret
 * code.
 * @param secret_code_max_digit The maximum digit allowed in the secret
 * code.
 * @return std::vector<int> A vector containing the player's guess.
 */
std::string InputGuess(WINDOW *window, int &y, std::string prompt,
                       const int &secret_code_length,
                       const int &secret_code_min_digit,
                       const int &secret_code_max_digit,
                       const bool &is_single = false);
std::vector<int> ToVector(std::string input);

/**
 * @brief Prints the player's guess and the feedback.
 *
 * @param guess The player's guess.
 * @param feedback The feedback for the guess.
 */
void PrintGuess(const std::vector<int> &guess, const std::string &feedback);
void PrintGuess(WINDOW *window, int &y, int x, const std::vector<int> &guess,
                const std::string &feedback);

/**
 * @brief Prints the player's secret code.
 *
 * @param code The player's secret code.
 */
void PrintCode(std::vector<int> code);
void PrintCode(WINDOW *window, int &y, int x, std::vector<int> code);

/**
 * @brief Prompts the player to select the game difficulty or to go back to the
 * previous screen.
 *
 * @param window The window to display the selection.
 * @return int The player's selection.
 */
int InputDifficulty(WINDOW *window);
} // namespace player
#endif // PLAYER_UTIL_UTIL_H_
