#include "menu.h"

#include "../util/util.h"

#include <iostream>

int Menu() {
  Title();
  std::cout << "1. Play\n";
  std::cout << "2. Instructions\n";
  std::cout << "3. Exit\n";
  std::cout << "Enter your choice: ";
  int choice = inputInteger("Enter your choice: ", 1, 3);
  return choice;
}

void Instructions() {
  Title();
  std::cout << "Instructions:\n";
  std::cout << "1. The computer will generate a secret code consisting of 4 "
               "numbers.\n";
  std::cout << "2. The numbers in the secret code will be between 0 and 7.\n";
  std::cout << "3. You have to guess the secret code.\n";
  std::cout << "4. After each guess, the computer will give you feedback.\n";
  std::cout << "5. The feedback will consist of 2 numbers:\n";
  std::cout << "   - The first number represents the number of correct digits "
               "in the correct position.\n";
  std::cout << "   - The second number represents the number of correct digits "
               "in the wrong position.\n";
  std::cout << "6. You have 10 chances to guess the secret code.\n";
  std::cout << "7. If you guess the secret code within 10 chances, you win.\n";
  std::cout << "8. If you are unable to guess the secret code within 10 "
               "chances, you lose.\n";
  std::cout << "9. Good luck!\n\n";
}

void Title() {
  clearScreen();
  // TODO: get terminal width dynamically
  std::cout << "                                      _ _ _ ____ _    ____ ____ _  _ ____     ___ ____\n";
  std::cout << "                                      | | | |___ |    |    |  | |\\/| |___      |  |  |\n";
  std::cout << "                                      |_|_| |___ |___ |___ |__| |  | |___      |  |__|\n\n";
  std::cout << ANSI_COLOR_BLUE;
  std::cout << "███╗   ███╗ █████╗ ███████╗████████╗███████╗██████╗ ███╗   ███╗██╗███╗   ██╗██████╗       ██████╗  █████╗ ███╗   ███╗███████╗\n";
  std::cout << "████╗ ████║██╔══██╗██╔════╝╚══██╔══╝██╔════╝██╔══██╗████╗ ████║██║████╗  ██║██╔══██╗     ██╔════╝ ██╔══██╗████╗ ████║██╔════╝\n";
  std::cout << "██╔████╔██║███████║███████╗   ██║   █████╗  ██████╔╝██╔████╔██║██║██╔██╗ ██║██║  ██║     ██║  ███╗███████║██╔████╔██║█████╗\n";
  std::cout << "██║╚██╔╝██║██╔══██║╚════██║   ██║   ██╔══╝  ██╔══██╗██║╚██╔╝██║██║██║╚██╗██║██║  ██║     ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝\n";
  std::cout << "██║ ╚═╝ ██║██║  ██║███████║   ██║   ███████╗██║  ██║██║ ╚═╝ ██║██║██║ ╚████║██████╔╝     ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗\n";
  std::cout << "╚═╝     ╚═╝╚═╝  ╚═╝╚══════╝   ╚═╝   ╚══════╝╚═╝  ╚═╝╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═════╝       ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝\n";
  std::cout << ANSI_COLOR_RESET;
  std::cout << "                                ___  _   _    ____ _  _ _ _   _ ____ ___    ___  ____ _  _ _\n";
  std::cout << "                                |__]  \\_/     |  | |  | |  \\_/  |___  |     |__] |__/ |  | |\n";
  std::cout << "                                |__]   |      |_\\| |__| |   |   |___  |     |__] |  \\ |__| |___\n\n";
}

void Congratulations() {
  clearScreen();
  std::cout << ANSI_COLOR_GREEN;
  std::cout << " ██████╗ ██████╗ ███╗   ██╗ ██████╗ ██████╗  █████╗ ████████╗██╗   ██╗ █████╗ ████████╗██╗ ██████╗ ███╗   ██╗███████╗\n";
  std::cout << "██╔════╝██╔═══██╗████╗  ██║██╔════╝ ██╔══██╗██╔══██╗╚══██╔══╝██║   ██║██╔══██╗╚══██╔══╝██║██╔═══██╗████╗  ██║██╔════╝\n";
  std::cout << "██║     ██║   ██║██╔██╗ ██║██║  ███╗██████╔╝███████║   ██║   ██║   ██║███████║   ██║   ██║██║   ██║██╔██╗ ██║███████╗\n";
  std::cout << "██║     ██║   ██║██║╚██╗██║██║   ██║██╔══██╗██╔══██║   ██║   ██║   ██║██╔══██║   ██║   ██║██║   ██║██║╚██╗██║╚════██║\n";
  std::cout << "╚██████╗╚██████╔╝██║ ╚████║╚██████╔╝██║  ██║██║  ██║   ██║   ╚██████╔╝██║  ██║   ██║   ██║╚██████╔╝██║ ╚████║███████║\n";
  std::cout << " ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝\n\n";
  std::cout << ANSI_COLOR_RESET;
}

void TryAgain() {
  clearScreen();
  std::cout << ANSI_COLOR_RED;
  std::cout << "████████╗██████╗ ██╗   ██╗      █████╗  ██████╗  █████╗ ██╗███╗   ██╗\n";
  std::cout << "╚══██╔══╝██╔══██╗╚██╗ ██╔╝     ██╔══██╗██╔════╝ ██╔══██╗██║████╗  ██║\n";
  std::cout << "   ██║   ██████╔╝ ╚████╔╝      ███████║██║  ███╗███████║██║██╔██╗ ██║\n";
  std::cout << "   ██║   ██╔══██╗  ╚██╔╝       ██╔══██║██║   ██║██╔══██║██║██║╚██╗██║\n";
  std::cout << "   ██║   ██║  ██║   ██║        ██║  ██║╚██████╔╝██║  ██║██║██║ ╚████║\n";
  std::cout << "   ╚═╝   ╚═╝  ╚═╝   ╚═╝        ╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝\n\n";
  std::cout << ANSI_COLOR_RESET;
}

void Goodbye() {
  clearScreen();
  std::cout << ANSI_COLOR_MAGENTA;
  std::cout << " ██████╗  ██████╗  ██████╗ ██████╗ ██████╗ ██╗   ██╗███████╗\n";
  std::cout << "██╔════╝ ██╔═══██╗██╔═══██╗██╔══██╗██╔══██╗╚██╗ ██╔╝██╔════╝\n";
  std::cout << "██║  ███╗██║   ██║██║   ██║██║  ██║██████╔╝ ╚████╔╝ █████╗\n";
  std::cout << "██║   ██║██║   ██║██║   ██║██║  ██║██╔══██╗  ╚██╔╝  ██╔══╝\n";
  std::cout << "╚██████╔╝╚██████╔╝╚██████╔╝██████╔╝██████╔╝   ██║   ███████╗\n";
  std::cout << " ╚═════╝  ╚═════╝  ╚═════╝ ╚═════╝ ╚═════╝    ╚═╝   ╚══════╝\n\n";
  std::cout << ANSI_COLOR_RESET;
}
