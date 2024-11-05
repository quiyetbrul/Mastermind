/**
 * @file util.h
 * @brief Declarations for utility functions used by the player.
 */

#ifndef PLAYER_UTIL_UTIL_H_
#define PLAYER_UTIL_UTIL_H_

#include <string>
#include <vector>

namespace player {
/**
 * @brief Generates feedback for a guess based on the secret code.
 *
 * @param guess The guess to be evaluated.
 * @param code The secret code to compare the guess against.
 * @param secret_code_length The length of the secret code.
 * @return A string containing the feedback for the guess.
 */
std::string GiveFeedback(const std::vector<int> &guess,
                         const std::vector<int> &code,
                         const int &secret_code_length);

/**
 * @brief Generates a hint for the player based on the guess and the secret
 * code.
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

/**
 * @brief Prompts the player to input a guess.
 *
 * @param prompt The prompt to display to the player.
 * @param secret_code_length The length of the secret code.
 * @param secret_code_min_digit The minimum digit allowed in the secret code.
 * @param secret_code_max_digit The maximum digit allowed in the secret code.
 * @return A vector containing the player's guess.
 */
std::vector<int> InputGuess(const std::string &prompt,
                            const int &secret_code_length,
                            const int &secret_code_min_digit,
                            const int &secret_code_max_digit);

/**
 * @brief Prints the player's guess and the feedback.
 *
 * @param guess The player's guess.
 * @param feedback The feedback for the guess.
 */
void PrintGuess(const std::vector<int> &guess, const std::string &feedback);

/**
 * @brief Prints the player's secret code.
 *
 * @param code The player's secret code.
 */
void PrintCode(std::vector<int> code);
} // namespace player
#endif // PLAYER_UTIL_UTIL_H_
