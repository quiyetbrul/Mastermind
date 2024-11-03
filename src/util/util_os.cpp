#include "util.h"

#include <iostream>

// TODO: ask whether game needs to be cross-platform
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

void ClearScreen() { system("clear"); }

void CloseTerminal() { exit(0); }

void SetTerminalSize(const int &width, const int &height) {
  struct winsize size;
  size.ws_col = width;
  size.ws_row = height;
  if (ioctl(STDOUT_FILENO, TIOCSWINSZ, &size) == -1) {
    perror("ioctl");
  } else {
    std::cout << "\033[8;" << height << ";" << width
              << "t"; // ANSI escape code to resize terminal
  }
}

void SetTerminalTitle(const std::string &title) {
  std::cout << "\033]0;" << title << "\007";
}
