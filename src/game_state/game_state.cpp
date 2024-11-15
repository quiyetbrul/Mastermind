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

#include <ncurses.h>

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
  QUICK_GAME = 1, /**< Quick game mode */
  CODEMASTER,     /**< Play as codemaster */
  BACK            /**< Go back to main menu */
};

namespace mastermind {
GameState::GameState() {
  Logger::GetInstance().Log("Initializing game state");

  SetTerminalSize(kTerminalWidth, kTerminalHeight);
  SetTerminalTitle("Mastermind Game by Quiyet Brul");

  initscr();

  getmaxyx(stdscr, y_max_, x_max_);

  banner_window_ = newwin(10, x_max_, 0, 0);
  game_window_ = newwin(20, x_max_, 10, 0);

  score_.SetWindow(game_window_);
  load_.SetWindow(game_window_);

  start_color();

  curs_set(0); // hide the cursor
  box(banner_window_, 0, 0);
  box(game_window_, 0, 0);
  keypad(game_window_, true); // enable function keys, e.g. arrow keys
}

void GameState::Start() {
  Title(banner_window_);

  std::vector<std::string> choices = {"Play", "Load Game", "Scoreboard",
                                      "Instructions", "Exit"};
  int choice = 0;
  int highlight = 0;

  while (true) {
    wrefresh(game_window_);
    PrintMenu(game_window_, highlight, choices);
    choice = wgetch(game_window_);
    switch (choice) {
    case KEY_UP:
      --highlight;
      if (highlight < 0)
        highlight = choices.size() - 1;
      break;
    case KEY_DOWN:
      ++highlight;
      if (highlight >= choices.size())
        highlight = 0;
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
  std::vector<std::string> choices = {"Quick Game", "Codemaster", "Back"};

  int choice = 0;
  int highlight = 0;

  wclear(game_window_);
  wrefresh(game_window_);

  while (true) {
    wrefresh(game_window_);
    PrintMenu(game_window_, highlight, choices);
    choice = wgetch(game_window_);
    switch (choice) {
    case KEY_UP:
      --highlight;
      if (highlight < 0)
        highlight = choices.size() - 1;
      break;
    case KEY_DOWN:
      ++highlight;
      if (highlight >= choices.size())
        highlight = 0;
      break;
    case 10:
      switch (static_cast<GameType>(highlight + 1)) {
      case GameType::QUICK_GAME: {
        player::Single quick_game;
        quick_game.Start();
        break;
      }
      case GameType::CODEMASTER: {
        player::Codemaster codemaster_player;
        codemaster_player.Start();
        break;
      }
      case GameType::BACK:
        wclear(game_window_);
        wrefresh(game_window_);
        return;
      }
    }
  }
}

void GameState::LoadGameMenu() {
  Logger::GetInstance().Log("Printing saved games");
  load_.PrintGames();
  if (load_.GetCount() != 0) {
    load_.SelectGame();
    load_.Start();
  }
}

void GameState::Scoreboard() {
  Logger::GetInstance().Log("Printing scoreboard");
  score_.PrintScores();
}

void GameState::Instructions() {
  Logger::GetInstance().Log("Printing instructions");
  PrintInstructions(game_window_);
}
} // namespace mastermind
