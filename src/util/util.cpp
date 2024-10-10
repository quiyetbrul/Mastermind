#include "util.h"

#include <cstdlib>
#include <iostream>

// TODO: separate OS specific code



// TODO: use API to generate random number
int gen_random(const int &min, const int &max) {
  return rand() % (max - min + 1) + min;
}

int inputInteger(std::string prompt, int startRange, int endRange) {
  int input;
  do {
    std::cout << prompt;
    try {
      std::cin >> input;
      if (std::cin.fail() || input < startRange || input > endRange) {
        std::cin.clear(); // clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                        '\n'); // discard invalid input
        std::cout << "Invalid input. Please enter a valid input between "
                  << startRange << " and " << endRange << std::endl;
      } else
        break;
    } catch (std::invalid_argument &e) {
      std::cout << e.what() << std::endl;
    }
  } while (true);
  return input;
}
