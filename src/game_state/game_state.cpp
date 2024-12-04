/**
 * @file game_state.cpp
 * @brief Implementation of GameState class.
 */

#include "game_state.h"

#include <ncurses.h>
#include <string>

#include "logger/logger.h"
#include "player/type/codemaster/codemaster.h"
#include "player/type/one_player/one_player.h"
#include "player/type/timed/timed.h"
#include "ui/ui.h"
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
  ONE_PLAYER = 1, /**< One player mode */
  TWO_PLAYER,     /**< Two player mode */
  TIMED,          /**< Timed mode */
  CODEMASTER,     /**< Play as codemaster */
  BACK            /**< Go back to main menu */
};

namespace mastermind {
GameState::GameState() {
  logger_.Log("Initializing GameState");

  SetTerminalSize(kTerminalWidth, kTerminalHeight);
  SetTerminalTitle("Mastermind Game by Quiyet Brul");

  initscr();

  getmaxyx(stdscr, y_max_, x_max_);

  banner_window_ = newwin(y_max_ * (1 / 3.0), x_max_, 0, 0);
  game_window_ = newwin(y_max_ * (2 / 3.0), x_max_, y_max_ * (1 / 3.0), 0);

  start_color();
  init_pair(1, COLOR_CYAN, COLOR_BLACK);
  init_pair(2, COLOR_MAGENTA, COLOR_BLACK);

  curs_set(0);
  scrollok(game_window_, false);
  keypad(game_window_, true);
  noecho();
}

void GameState::Start() {
  Title(banner_window_);

  std::vector<std::string> choices = {"Play", "Load Game", "Scoreboard",
                                      "Instructions", "Exit"};
  int highlight = 0;

  PrintHL(game_window_);

  while (true) {
    wclear(game_window_);
    UserChoice(game_window_, highlight, choices, "Main Menu");
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
      CloseTerminal();
      logger_.CloseOutputFile();
      return; // Exit the function to close the program
    }
  }
}

void GameState::PlayerMenu() {
  wclear(game_window_);

  std::vector<std::string> choices = {"1 Player", "Codemaster", "Back"};

  int choice = 0;
  int highlight = 0;

  while (true) {
    UserChoice(game_window_, highlight, choices, "Select Player Type");
    switch (static_cast<GameType>(highlight + 1)) {
    case GameType::ONE_PLAYER: {
      player::OnePlayer one_player;
      one_player.SetWindow(game_window_);
      one_player.Start();
      if (one_player.IsGameFinished()) {
        return;
      }
      break;
    }
    case GameType::TWO_PLAYER: {
      // TODO: "Implement two player mode";
      break;
    }
    case GameType::TIMED: {
      // TODO: WIP
      player::Timed timed_player;
      timed_player.SetWindow(game_window_);
      timed_player.Start();
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
