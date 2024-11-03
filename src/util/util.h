#ifndef UTIL_UTIL_H_
#define UTIL_UTIL_H_

#include <functional>
#include <iostream>
#include <limits>
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
#define DELETE_LINE "\033[A\033[K"

void ClearScreen();

void CloseTerminal();

void SetTerminalSize(const int &width = kTerminalWidth,
                     const int &height = kTerminalHeight);

void SetTerminalTitle(const std::string &title);

std::vector<int> GenRandom(const int &generate, const int &min, const int &max);
int RandomNumber(const int &min, const int &max);

// TODO: think where this should be. UI maybe? it deals with menus
inline void ReturnTo(const std::string &where,
                     const std::function<void()> &function) {
  std::cout << "Press enter key to return to " << where << std::endl;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cin.get();
  std::cin.clear();
  function();
}

std::string InputString(const std::string &prompt);

int InputInteger(const std::string prompt, const int &start_range,
                 const int &end_range);

char InputChar(const std::string &prompt, const char &yes, const char &no);

#endif // UTIL_UTIL_H_
