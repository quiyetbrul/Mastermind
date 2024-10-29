#ifndef GAMEPLAY_UTIL_H_
#define GAMEPLAY_UTIL_H_

#include <string>
#include <vector>

#include "player/computer/codebreaker/codebreaker.h"
#include "player/player.h"

void PlayGameLoop(Player &player, Codebreaker *computer = nullptr,
                  std::vector<int> initial_guess = {});

std::string GiveFeedback(std::vector<int> guess, std::vector<int> code);

void PrintGuesses(
    const std::vector<std::pair<std::vector<int>, std::string>> &guesses);

void PrintCode(std::vector<int> code);

std::vector<int> InputGuess(const std::string &prompt);

#endif // GAMEPLAY_UTIL_H_
