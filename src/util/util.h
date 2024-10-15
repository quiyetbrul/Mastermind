#ifndef UTIL_H_
#define UTIL_H_

#include <string>

// TODO: move to definitions file

const int kTerminalWidth = 125;
const int kTerminalHeight = 24;

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_RESET "\x1b[0m"
#define ANSI_BLINK "\x1b[5m"

const int kMinSecretCodeDigit = 0;
const int kMaxSecretCodeDigit = 7;
const int kSecretCodeLength = 4;

// TODO: inline these small functions

void ClearScreen();

void CloseTerminal();

void SetTerminalSize(const int &width = kTerminalWidth,
                     const int &height = kTerminalHeight);

void SetTerminalTitle(const std::string &title);

std::string GenRandom(const int &generate, const int &min, const int &max);
int RandomNumber(const int &min, const int &max);

int InputInteger(const std::string prompt, const int &start_range,
                 const int &end_range);

char InputChar(const std::string &prompt, const char &yes, const char &no);

std::string InputGuess(const std::string &prompt);

#endif // UTIL_H_
