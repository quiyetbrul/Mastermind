#ifndef PLAYER_UTIL_UTIL_H_
#define PLAYER_UTIL_UTIL_H_

#include <string>
#include <utility>
#include <vector>

std::string GiveFeedback(std::vector<int> guess, std::vector<int> code);
void PrintGuesses(
    const std::vector<std::pair<std::vector<int>, std::string>> &guesses);
void PrintCode(std::vector<int> code);

#endif // PLAYER_UTIL_UTIL_H_
