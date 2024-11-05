/**
 * @file game_state.cpp
 * @brief Implementation of GameState class.
 */

#include "game_state.h"

#include <iostream>
#include <string>

#include "logger/logger.h"
#include "player/computer/computer.h"
#include "player/single/single.h"
#include "ui/banner.h"
#include "ui/menu.h"
#include "util/util.h"

/**
 * @enum MainMenu
 * @brief Represents the main menu options.
 */
enum class MainMenu : int {
  PLAY = 1,     /**< Start a new game */
  LOAD,         /**< Load a saved game */
  SCOREBOARD,   /**< View the scoreboard */
  INSTRUCTIONS, /**< View the game instructions */
  EXIT          /**< Exit the game */
};

/**
 * @enum PlayerType
 * @brief Represents the types of players.
 */
enum class PlayerType : int {
  SINGLE = 1, /**< Single player mode */
  COMPUTER    /**< Play against the computer */
};

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
    Logger::GetInstance().Log("Printing saved games");
    std::cout << "Load Game under construction" << std::endl;
    break;
  case MainMenu::SCOREBOARD:
    // TODO: PRINT SCORE ASCII ART
    Logger::GetInstance().Log("Printing scoreboard");
    scoreboard_.PrintScores();
    break;
  case MainMenu::INSTRUCTIONS:
    Logger::GetInstance().Log("Printing instructions");
    PrintInstructions();
    break;
  case MainMenu::EXIT:
    Goodbye();
    CloseTerminal();
    break;
  }
  ReturnTo("Main Menu", [this]() { Start(); });
}

void GameState::Init() {
  Logger::GetInstance().Log("Initializing game state");
  SetTerminalSize(kTerminalWidth, kTerminalHeight);
  SetTerminalTitle("Mastermind Game by Quiyet Brul");
  scoreboard_.Init();
  saved_games_.Init();
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
  default:
    // TODO: this will never be reached. think!
    ReturnTo("Main Menu", [this]() { Start(); });
    // Start(); // use Return To instead?
    break;
  }
  // TODO: maybe just have user enter and return to Start()
  PlayAgain();
}

void GameState::PlayAgain() {
  char play_again = InputChar("Do you want to play again? (y/n): ", 'y', 'n');
  play_again == 'y' ? PlayerMenu() : Start();
}
} // namespace mastermind
