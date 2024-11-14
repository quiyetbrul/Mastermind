/**
 * @file game_state.cpp
 * @brief Implementation of GameState class.
 */

#include "game_state.h"

#include <cstdlib>
#include <ncurses.h>
#include <string>

#include "load_game/load_game.h"
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
  QUICK_GAME = 1, /**< Quick game mode */
  CODEMASTER,     /**< Play as codemaster */
  BACK            /**< Go back to main menu */
};

namespace mastermind {
void GameState::Start() {
  box(title_win_, 0, 0);
  box(menu_win_, 0, 0);
  keypad(menu_win_, true); // enable function keys, e.g. arrow keys

  std::vector<std::string> choices = {"Play", "Load Game", "Scoreboard",
                                      "Instructions", "Exit"};
  int choice = 0;
  int highlight = 0;

  Title(title_win_);

  while (true) {
    refresh();
    Title(title_win_);
    PrintMenu(menu_win_, highlight, choices);
    choice = wgetch(menu_win_);
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
        // PlayerMenu(menu_win_);
        break;
      case MainMenu::LOAD: {
        // LoadGameMenu(menu_win_);
        break;
      }
      case MainMenu::SCOREBOARD:
        // TODO: PRINT SCORE ASCII ART
        // Scoreboard(menu_win_);
        break;
      case MainMenu::INSTRUCTIONS:
        Logger::GetInstance().Log("Printing instructions");
        PrintInstructions(menu_win_, 0, 10);
        break;
      case MainMenu::EXIT:
        wclear(title_win_);
        wclear(menu_win_);
        wrefresh(title_win_);
        wrefresh(menu_win_);
        refresh();
        delwin(title_win_);
        delwin(menu_win_);
        return; // Exit the function to close the program
      }
    }
  }
}

void GameState::Init() {
  Logger::GetInstance().Log("Initializing game state");
  SetTerminalSize(kTerminalWidth, kTerminalHeight);
  SetTerminalTitle("Mastermind Game by Quiyet Brul");
  initscr();
  getmaxyx(stdscr, y_max_, x_max_);
  title_win_ = newwin(10, x_max_, 0, 0);
  menu_win_ = newwin(20, x_max_, 10, 0);
  curs_set(0); // hide the cursor
  start_color();
}

void GameState::PlayerMenu(WINDOW *window) {
  PrintPlayerMenu();
  const int min_choice = static_cast<int>(GameType::QUICK_GAME);
  const int max_choice = static_cast<int>(GameType::BACK);
  int user_choice = InputInteger("Enter your choice: ", min_choice, max_choice);
  switch (static_cast<GameType>(user_choice)) {
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
    break;
  }
  Start();
}

void GameState::LoadGameMenu(WINDOW *window) {
  Logger::GetInstance().Log("Printing saved games");
  game_loader::LoadGame load;
  load.PrintGames();
  if (load.GetCount() != 0) {
    load.SelectGame();
    load.Start();
  }
}

void GameState::Scoreboard(WINDOW *window) {
  Logger::GetInstance().Log("Printing scoreboard");
  score_.PrintScores();
}
} // namespace mastermind
