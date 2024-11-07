/**
 * @file game_state.cpp
 * @brief Implementation of GameState class.
 */

#include "game_state.h"

#include <iostream>
#include <string>

#include "game_type/codemaster/codemaster.h"
#include "game_type/freeplay/freeplay.h"
#include "game_type/quick_game/quick_game.h"
#include "game_type/timed_game/timed_game.h"
#include "logger/logger.h"
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
// TODO: change names
enum class GameType : int {
  FREEPLAY = 1, /**< Freeply mode */
  QUICK_GAME,   /**< Quick game mode */
  TIMED_GAME,   /**< Timed game mode */
  CODEMASTER    /**< Play as codemaster */
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
  const int min_choice = static_cast<int>(GameType::FREEPLAY);
  const int max_choice = static_cast<int>(GameType::CODEMASTER);
  int user_choice = InputInteger("Enter your choice: ", min_choice, max_choice);
  switch (static_cast<GameType>(user_choice)) {
  case GameType::FREEPLAY: {
    game_type::Freeplay freeplay;
    freeplay.Start();
    break;
  }
  case GameType::QUICK_GAME: {
    game_type::QuickGame quick_game;
    quick_game.Start();
    break;
  }
  case GameType::TIMED_GAME: {
    game_type::TimedGame timed_game;
    timed_game.Start();
    break;
  }
  case GameType::CODEMASTER: {
    game_type::Codemaster codemaster_player;
    codemaster_player.Start();
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
