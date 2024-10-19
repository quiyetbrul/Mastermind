#include "gameplay.h"

#include <iostream>
#include <string>

#include "../ui/menu.h"
#include "../ui/print.h"
#include "../util/util.h"
#include "codebreaker/codebreaker.h"

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
    // LoadGame();
    std::cout << "Load Game under construction" << std::endl;
    break;
  case 3:
    // Scoreboard();
    std::cout << "Scoreboard under construction" << std::endl;
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
  switch (player_choice) {
  case 1:
    SinglePlayer();
    break;
  case 2:
    ComputerCodebreaker();
    break;
  }
}

void Gameplay::SinglePlayer() {
  Title();

  std::vector<std::pair<std::string, std::string>> user_guess_history;
  Player player_one;
  player_one.SetSecretCode(
      GenRandom(kSecretCodeLength, kMinSecretCodeDigit, kMaxSecretCodeDigit));
  player_one.SetGuesses(user_guess_history);

  // TODO: DRY this up
  while (player_one.GetLife() > 0) {
    std::string user_guess = InputGuess("Enter your guess: ");
    std::string_view view_input = user_guess;
    if (view_input == "/save") {
      SaveGame(player_one);
    }
    if (user_guess == player_one.GetSecretCode()) {
      Congratulations();
      std::cout << player_one.GetSecretCode() << std::endl;
      // TODO: update scoreboard
      break;
    }
    player_one.AddGuess(user_guess,
                        GiveFeedback(player_one.GetSecretCode(), user_guess));
    PrintGuesses(player_one.GetGuesses());
    player_one.DecrementLife();
    if (player_one.GetLife() == 0) {
      TryAgain();
      std::cout << player_one.GetSecretCode() << std::endl;
    }
  }

  PlayAgain();
}

void Gameplay::ComputerCodebreaker() {
  Title();

  std::vector<std::pair<std::string, std::string>> computer_guess_history;
  Player player_computer;
  player_computer.SetSecretCode(
      GenRandom(kSecretCodeLength, kMinSecretCodeDigit, kMaxSecretCodeDigit));
  player_computer.SetGuesses(computer_guess_history);

  Codebreaker computer(kSecretCodeLength, kMinSecretCodeDigit,
                       kMaxSecretCodeDigit);

  while (player_computer.GetLife() > 0) {
    std::string computer_guess =
        computer.MakeGuess(); // Use MakeGuess to get a guess
    std::string feedback =
        GiveFeedback(player_computer.GetSecretCode(), computer_guess);
    computer.ReceiveFeedback(feedback); // Update Codebreaker with the feedback

    if (computer_guess == player_computer.GetSecretCode()) {
      Congratulations();
      std::cout << player_computer.GetSecretCode() << std::endl;
      break;
    }

    player_computer.AddGuess(computer_guess, feedback);
    PrintGuesses(player_computer.GetGuesses());
    player_computer.DecrementLife();

    if (player_computer.GetLife() == 0) {
      TryAgain();
      std::cout << player_computer.GetSecretCode() << std::endl;
    }
  }

  PlayAgain();
}

// TODO: add record
void Gameplay::SaveGame(const Player &player) {
  std::string game_name = InputString("Enter the name of the game: ");
  std::string password = InputString("Enter a password for the game: ");
  Games game(game_name, password, player);

  if (saved_games_.size() >= save_limit_) {
    std::cout << "Only " << save_limit_ << " games can be saved at a time."
              << std::endl;
    char overwrite =
        InputChar("Do you want to overwrite a game? (y/n): ", 'y', 'n');
    if (overwrite == 'y') {
      OverwriteGame(game);
    }
  } else {
    saved_games_.push_back(game);
  }
  // TODO: update record of saved games
  Start();
}

// TODO: this is menu
// update record
void Gameplay::OverwriteGame(const Games &game) {
  for (int i = 0; i < saved_games_.size(); i++) {
    std::cout << i << ". " << saved_games_[i].GetGameName() << std::endl;
    std::cout << "\tLife: " << saved_games_[i].GetPlayer().GetLife() << std::endl;
    std::cout << "\tLast guess: "
              << saved_games_[i].GetPlayer().GetGuesses().back().first
              << std::endl;
    std::cout << "\tLast feedback: "
              << saved_games_[i].GetPlayer().GetGuesses().back().second
              << std::endl;
  }
  int to_overwrite = InputInteger(
      "Enter the number of the game to overwrite: ", 0, saved_games_.size());
  saved_games_[to_overwrite] = game;
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

void Gameplay::CheckGameOver(int &life, const std::string &secret_code) {
  if (--life == 0) {
    TryAgain();
    std::cout << secret_code << std::endl;
  }
}

std::string Gameplay::GiveFeedback(const std::string &secret_code,
                                   const std::string &guesses) {
  int correct_position = 0;
  int correct_digit = 0;

  // Vectors to keep track of unmatched digits
  std::vector<bool> matched_secret(kSecretCodeLength, false);
  std::vector<bool> matched_guess(kSecretCodeLength, false);
  std::array<int, 10> secret_count = {0};

  // First pass: mark exact matches and count remaining digits in secret_code
  for (int i = 0; i < kSecretCodeLength; i++) {
    if (guesses[i] == secret_code[i]) {
      correct_position++;
      matched_secret[i] = true;
      matched_guess[i] = true;
    } else {
      secret_count[secret_code[i] - '0']++;
    }
  }

  // Second pass: count correct digits in wrong positions
  for (int i = 0; i < kSecretCodeLength; i++) {
    if (!matched_guess[i] && secret_count[guesses[i] - '0'] > 0) {
      correct_digit++;
      secret_count[guesses[i] - '0']--;
    }
  }

  if (correct_position == 0 && correct_digit == 0) {
    return std::string(ANSI_COLOR_RED) + "No correct digit" + ANSI_RESET;
  }

  std::string feedback = "";
  for (int i = 0; i < correct_position; i++) {
    feedback += std::string(ANSI_COLOR_GREEN) + "B" + ANSI_RESET;
  }

  for (int i = 0; i < correct_digit; i++) {
    feedback += std::string(ANSI_COLOR_YELLOW) + "W" + ANSI_RESET;
  }

  return feedback;
}

void Gameplay::PrintGuesses(
    const std::vector<std::pair<std::string, std::string>> &guesses) {
  Title();
  for (const auto &i : guesses) {
    for (const auto &c : i.first) {
      std::cout << c << " ";
    }
    std::cout << "   " << i.second << std::endl;
  }
}

std::string Gameplay::InputGuess(const std::string &prompt) {
  std::string input;
  while (true) {
    std::cout << prompt;
    std::cin >> input;

    // `std::string_view` offers better performance with string comparisons
    // by avoiding copying the string
    std::string_view view_input = input;
    if (view_input == "/save") {
      break;
    }

    if (input.length() != kSecretCodeLength) {
      std::cout << "Input must be exactly " << kSecretCodeLength
                << " digits long." << std::endl;
      continue;
    }

    bool valid = true;
    for (char c : input) {
      if (!isdigit(c) || c < '0' || c > '7') {
        std::cout << "Each digit must be between 0 and 7." << std::endl;
        valid = false;
        break;
      }
    }

    if (valid) {
      break;
    }
  }
  return input;
}
