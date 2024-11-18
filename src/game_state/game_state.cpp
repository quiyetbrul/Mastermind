/**
 * @file game_state.cpp
 * @brief Implementation of GameState class.
 */

#include "game_state.h"

#include <string>

#include "logger/logger.h"
#include "player/type/codemaster/codemaster.h"
#include "player/type/single/single.h"
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
enum class GameType : int {
  SINGLE_PLAYER = 1, /**< Single player mode */
  CODEMASTER,        /**< Play as codemaster */
  BACK               /**< Go back to main menu */
};

namespace mastermind {
GameState::GameState() {
  logger_.Log("Initializing game state");

  SetTerminalSize(kTerminalWidth, kTerminalHeight);
  SetTerminalTitle("Mastermind Game by Quiyet Brul");

  initscr();

  getmaxyx(stdscr, y_max_, x_max_);

  banner_window_ = newwin(10, x_max_, 0, 0);
  game_window_ = newwin(20, x_max_, 10, 0);

  start_color();

  curs_set(0);
  noecho();
  keypad(game_window_, true);
}

void GameState::Start() {
  Title(banner_window_);

  std::vector<std::string> choices = {"Play", "Load Game", "Scoreboard",
                                      "Instructions", "Exit"};
  int choice = 0;
  int highlight = 0;

  while (true) {
    wclear(game_window_);
    PrintHL(game_window_, x_max_);
    PrintMenu(game_window_, highlight, choices, "Main Menu");
    choice = wgetch(game_window_);
    switch (choice) {
    case KEY_UP:
      UpdateHighlight(highlight, choices, -1);
      break;
    case KEY_DOWN:
      UpdateHighlight(highlight, choices, 1);
      break;
    case 10:
      switch (static_cast<MainMenu>(highlight + 1)) {
      case MainMenu::PLAY:
        PlayerMenu();
        break;
      case MainMenu::LOAD: {
        LoadGameMenu();
        break;
      }
      case MainMenu::SCOREBOARD:
        Scoreboard();
        break;
      case MainMenu::INSTRUCTIONS:
        Instructions();
        break;
      case MainMenu::EXIT:
        // TODO: use signal handler to properly close the program when the x
        // button is clicked
        delwin(banner_window_);
        delwin(game_window_);
        endwin();
        ClearScreen();
        CloseTerminal();
        return; // Exit the function to close the program
      }
    }
  }
}

void GameState::PlayerMenu() {
  wclear(game_window_);

  std::vector<std::string> choices = {"Single Player", "Codemaster", "Back"};

  int choice = 0;
  int highlight = 0;

  while (true) {
    PrintMenu(game_window_, highlight, choices, "Select Player Type");
    choice = wgetch(game_window_);
    switch (choice) {
    case KEY_UP:
      UpdateHighlight(highlight, choices, -1);
      break;
    case KEY_DOWN:
      UpdateHighlight(highlight, choices, 1);
      break;
    case 10:
      switch (static_cast<GameType>(highlight + 1)) {
      case GameType::SINGLE_PLAYER: {
        player::Single single_player;
        single_player.SetWindow(game_window_);
        single_player.Start();
        if (single_player.IsGameFinished()) {
          return;
        }
        break;
      }
      case GameType::CODEMASTER: {
        player::Codemaster codemaster_player;
        codemaster_player.SetWindow(game_window_);
        codemaster_player.Start();
        if (codemaster_player.IsGameFinished()) {
          return;
        }
        break;
      }
      case GameType::BACK:
        wclear(game_window_);
        return;
      }
    }
  }
}

void GameState::LoadGameMenu() {
  logger_.Log("Printing saved games");
  load_.SetWindow(game_window_);
  load_.Start();
}

void GameState::Scoreboard() {
  logger_.Log("Printing scoreboard");
  score_.SetWindow(game_window_);
  score_.PrintScores();
}

void GameState::Instructions() {
  logger_.Log("Printing instructions");
  PrintInstructions(game_window_);
}
} // namespace mastermind
