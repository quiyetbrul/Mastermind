/**
 * @file util_os.cpp
 * @brief Implementation of OS-specific functions.
 */

#include "util.h"

#include <cstdlib>
#include <iostream>

// TODO: ask whether game needs to be cross-platform
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

void CloseTerminal() {
#ifdef _WIN32
  // Close terminal on Windows
  ExitProcess(0);
#else
  // Close terminal on Unix-like systems
  _exit(0);
#endif
}

void SetTerminalSize(const int &width, const int &height) {
#ifdef _WIN32
  HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE);
  if (h_out == INVALID_HANDLE_VALUE) {
    std::cerr << "Error getting handle" << std::endl;
    return;
  }

  // Set the screen buffer size
  COORD new_size;
  new_size.X = width;
  new_size.Y = height;
  if (!SetConsoleScreenBufferSize(h_out, new_size)) {
    std::cerr << "Error setting screen buffer size" << std::endl;
    return;
  }

  // Set the window size
  SMALL_RECT rect;
  rect.Left = 0;
  rect.Top = 0;
  rect.Right = width - 1;
  rect.Bottom = height - 1;
  if (!SetConsoleWindowInfo(h_out, TRUE, &rect)) {
    std::cerr << "Error setting window size" << std::endl;
    return;
  }
#else
  struct winsize size;
  size.ws_col = width;
  size.ws_row = height;
  if (ioctl(STDOUT_FILENO, TIOCSWINSZ, &size) == -1) {
    perror("ioctl");
  } else {
    std::cout << "\033[8;" << height << ";" << width
              << "t"; // ANSI escape code to resize terminal
  }
#endif
}

void SetTerminalTitle(const std::string &title) {
#ifdef _WIN32
  SetConsoleTitle(title.c_str());
#else
  std::cout << "\033]0;" << title << "\007";
#endif
}
