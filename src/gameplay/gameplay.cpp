#include "gameplay.h"

#include <iostream>
#include <string>
#include <thread>

#include "player/computer/computer.h"
#include "player/single/single.h"
#include "ui/menu.h"
#include "ui/print.h"
#include "util/util.h"

std::vector<Games> Gameplay::saved_games_;
const int Gameplay::kLifeStart;
const int Gameplay::save_limit_;

void Gameplay::Start() {
  int menu_choice = MainMenu();
  switch (menu_choice) {
  case 1:
    GameMenu();
    break;
  case 2:
    std::cout << "Load Game under construction" << std::endl;
    // pause for 1 second
    std::this_thread::sleep_for(std::chrono::seconds(1));
    Start();
    break;
  case 3:
    std::cout << "Scoreboard under construction" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    Start();
    break;
  case 4:
    Instructions();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    Start();
    break;
  case 5:
    Goodbye();
    CloseTerminal();
    break;
  }
}

void Gameplay::GameMenu() {
  int player_choice = PlayerMenu();
  if (player_choice == 1) {
    SinglePlayer single_player;
    single_player.Start();
  } else if (player_choice == 2) {
    ComputerPlayer computer_player;
    computer_player.Start();
  }
  PlayAgain();
}

void Gameplay::PlayAgain() {
  char play_again = InputChar("Do you want to play again? (y/n): ", 'y', 'n');
  if (play_again == 'y') {
    GameMenu();
  } else {
    // TODO: maybe we just exit out of program?
    Start();
  }
}
