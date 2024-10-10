#ifndef UTIL_H_
#define UTIL_H_

#include <string>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

void clearScreen();

void closeTerminal();

void setTerminalSize(const int &width, const int &height);

void setTerminalTitle(const std::string &title);

int gen_random(const int &min, const int &max);

int inputInteger(std::string prompt, int startRange, int endRange);

#endif // UTIL_H_
