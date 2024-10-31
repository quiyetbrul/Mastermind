#include "game_state.h"

#include <iostream>
#include <string>

#include "game_data/saved_games/saved_games.h"
#include "game_data/scoreboard/scoreboard.h"
#include "player/computer/computer.h"
#include "player/single/single.h"
#include "ui/menu.h"
#include "ui/print.h"
#include "util/util.h"

namespace mastermind {
void GameState::Start() {
  int menu_choice = MainMenu();
  switch (menu_choice) {
  case 1:
    Menu();
    break;
  case 2:
    std::cout << "Load Game under construction" << std::endl;
    // game_data::SavedGames::GetInstance().PrintSavedGames();
    // std::string load_game =
    //     InputString("Enter the name of the game you want to load: ");
    // while (!game_data::SavedGames::GetInstance().IsGamePresent(load_game)) {
    //   load_game = InputString("Game not found. Enter the name of the game you "
    //                           "want to load: ");
    // }
    // player::Single loaded_player =
    //     game_data::SavedGames::GetInstance().LoadGame(load_game);
    // loaded_player.Start();
    break;
  case 3:
    // TODO: PRINT SCORE ASCII ART
    game_data::Scoreboard::GetInstance().PrintScores();
    break;
  case 4:
    Instructions();
    break;
  case 5:
    Goodbye();
    CloseTerminal();
    break;
  }
  ReturnTo("Main Menu", [this]() { Start(); });
}

void GameState::Menu() {
  int player_choice = PlayerMenu();
  if (player_choice == 1) {
    player::Single single_player;
    single_player.Start();
  } else if (player_choice == 2) {
    player::Computer computer_player;
    computer_player.Start();
  }
  // TODO: maybe just have user enter and return to Start()
  PlayAgain();
}

void GameState::PlayAgain() {
  char play_again = InputChar("Do you want to play again? (y/n): ", 'y', 'n');
  play_again == 'y' ? Menu() : Start();
}
} // namespace mastermind
