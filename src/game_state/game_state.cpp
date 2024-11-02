#include "game_state.h"

#include <iostream>
#include <string>

#include "game_data/scoreboard/scoreboard.h"
#include "player/computer/computer.h"
#include "player/single/single.h"
#include "ui/banner.h"
#include "ui/menu.h"
#include "util/util.h"

enum class MainMenu { PLAY = 1, LOAD, SCOREBOARD, INSTRUCTIONS, EXIT };

enum class Difficulty { EASY = 1, MEDIUM, HARD };

enum class PlayerType { SINGLE = 1, COMPUTER };

namespace mastermind {
void GameState::Start() {
  PrintMenu();
  const int min_choice = static_cast<int>(MainMenu::PLAY);
  const int max_choice = static_cast<int>(MainMenu::EXIT);
  int user_choice = InputInteger("Enter your choice: ", min_choice, max_choice);
  switch (static_cast<MainMenu>(user_choice)) {
  case MainMenu::PLAY:
    PlayerMenu();
    break;
  case MainMenu::LOAD:
    std::cout << "Load Game under construction" << std::endl;
    break;
  case MainMenu::SCOREBOARD:
    // TODO: PRINT SCORE ASCII ART
    game_data::Scoreboard::GetInstance().PrintScores();
    break;
  case MainMenu::INSTRUCTIONS:
    PrintInstructions();
    break;
  case MainMenu::EXIT:
    Goodbye();
    CloseTerminal();
    break;
  }
  ReturnTo("Main Menu", [this]() { Start(); });
}

void GameState::PlayerMenu() {
  PrintPlayerMenu();
  const int min_choice = static_cast<int>(PlayerType::SINGLE);
  const int max_choice = static_cast<int>(PlayerType::COMPUTER);
  int user_choice = InputInteger("Enter your choice: ", min_choice, max_choice);
  switch (static_cast<PlayerType>(user_choice)) {
  case PlayerType::SINGLE: {
    player::Single single_player;
    single_player.Start();
    break;
  }
  case PlayerType::COMPUTER: {
    player::Computer computer_player;
    computer_player.Start();
    break;
  }
  }
  // TODO: maybe just have user enter and return to Start()
  PlayAgain();
}

void GameState::PlayAgain() {
  char play_again = InputChar("Do you want to play again? (y/n): ", 'y', 'n');
  play_again == 'y' ? PlayerMenu() : Start();
}
} // namespace mastermind
