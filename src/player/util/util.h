#ifndef PLAYER_UTIL_UTIL_H_
#define PLAYER_UTIL_UTIL_H_

#include <string>
#include <vector>

namespace player {
std::string GiveFeedback(const std::vector<int> &guess,
                         const std::vector<int> &code,
                         const int &secret_code_length);
std::vector<int> InputGuess(const std::string &prompt,
                            const int &secret_code_length,
                            const int &secret_code_min_digit,
                            const int &secret_code_max_digit);
void PrintGuess(const std::vector<int> &guess, const std::string &feedback);
void PrintCode(std::vector<int> code);
} // namespace player
#endif // PLAYER_UTIL_UTIL_H_
