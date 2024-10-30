#ifndef PLAYER_UTIL_UTIL_H_
#define PLAYER_UTIL_UTIL_H_

#include <string>
#include <vector>

std::string GiveFeedback(const std::vector<int> &guess,
                         const std::vector<int> &code);
std::vector<int> InputGuess(const std::string &prompt);
void PrintGuess(const std::vector<int> &guess, const std::string &feedback);
void PrintCode(std::vector<int> code);

#endif // PLAYER_UTIL_UTIL_H_
