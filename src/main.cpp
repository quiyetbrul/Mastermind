#include "gameplay/gameplay.h"

#include <ctime>
#include <iostream>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

const int TERMINAL_WIDTH = 125;
const int TERMINAL_HEIGHT = 24;

void setTerminalSize(const int &width, const int &height);

void setTerminalTitle(const std::string &title);

/**
 * @brief A Mastermind game clone in C++
 *
 * @return Returns 0 when execution is successful
 */
int main() {
  // Set terminal title
  setTerminalSize(TERMINAL_WIDTH, TERMINAL_HEIGHT);
  setTerminalTitle("Mastermind Game by Quiyet Brul");

  Gameplay gameplay;
  gameplay.gameplay();

  return 0;
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
