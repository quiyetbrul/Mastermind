#include "menu.h"

#include <iostream>

#include "ui/menu.h"
#include "ui/print.h"

int MainMenu() {
  Title();
  std::cout << "1. Play\n";
  std::cout << "2. Load Game\n";
  std::cout << "3. Scoreboard\n";
  std::cout << "4. Instructions\n";
  std::cout << "5. Exit\n";
  int choice = InputInteger("Enter your choice: ", 1, 5);
  return choice;
}

int PlayerMenu() {
  Title();
  std::cout << "1. Single Player\n";
  std::cout << "2. Computer as Codebreaker\n";
  int choice = InputInteger("Enter your choice: ", 1, 2);
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
  std::cout << "5. The feedback will characters 'B' and 'W':\n";
  std::cout << "   - 'B' represents digits in correct positions\n";
  std::cout << "   - 'W' represents digits in incorrect positions\n";
  std::cout << "6. You have 10 chances to guess the secret code.\n";
  std::cout << "7. If you guess the secret code within 10 chances, you win.\n";
  std::cout << "8. If you are unable to guess the secret code within 10 "
               "chances, you lose.\n";
  std::cout << "9. Good luck!\n\n";
}
