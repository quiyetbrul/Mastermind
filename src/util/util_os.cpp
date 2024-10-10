#include "util.h"

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void closeTerminal() {
#ifdef _WIN32
  // Close terminal on Windows
  ExitProcess(0);
#else
  // Close terminal on Unix-like systems
  exit(0);
#endif
}

void setTerminalSize(const int &width, const int &height) {
#ifdef _WIN32
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  if (hOut == INVALID_HANDLE_VALUE) {
    std::cerr << "Error getting handle" << std::endl;
    return;
  }

  // Set the screen buffer size
  COORD newSize;
  newSize.X = width;
  newSize.Y = height;
  if (!SetConsoleScreenBufferSize(hOut, newSize)) {
    std::cerr << "Error setting screen buffer size" << std::endl;
    return;
  }

  // Set the window size
  SMALL_RECT rect;
  rect.Left = 0;
  rect.Top = 0;
  rect.Right = width - 1;
  rect.Bottom = height - 1;
  if (!SetConsoleWindowInfo(hOut, TRUE, &rect)) {
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

void setTerminalTitle(const std::string &title) {
#ifdef _WIN32
  SetConsoleTitle(title.c_str());
#else
  std::cout << "\033]0;" << title << "\007";
#endif
}
