#include "gameplay.h"

#include <iostream>
#include <string>

#include "gameplay/codebreaker/codebreaker.h"
#include "util/gameplay_util.h"
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

  std::vector<std::pair<std::vector<int>, std::string>> user_guess_history;
  Player player_one;
  player_one.SetSecretCode(
      GenRandom(kSecretCodeLength, kMinSecretCodeDigit, kMaxSecretCodeDigit));
  player_one.SetGuesses(user_guess_history);

  // TODO: DRY this up
  while (player_one.GetLife() > 0) {
    std::vector<int> user_guess = InputGuess("Enter your guess: ");

    if (user_guess == player_one.GetSecretCode()) {
      Congratulations();
      for (const auto &i : player_one.GetSecretCode()) {
        std::cout << i << " ";
      }
      std::cout << std::endl;
      // TODO: update scoreboard
      break;
    }
    player_one.AddGuess(user_guess,
                        GiveFeedback(player_one.GetSecretCode(), user_guess));
    PrintGuesses(player_one.GetGuesses());
    player_one.DecrementLife();
    if (player_one.GetLife() == 0) {
      TryAgain();
      for (const auto &i : player_one.GetSecretCode()) {
        std::cout << i << " ";
      }
      std::cout << std::endl;
    }
  }

  PlayAgain();
}

void Gameplay::ComputerCodebreaker() {
  Title();

  std::vector<std::pair<std::vector<int>, std::string>> computer_guess_history;
  Player player_computer;
  player_computer.SetSecretCode(
      GenRandom(kSecretCodeLength, kMinSecretCodeDigit, kMaxSecretCodeDigit));
  player_computer.SetGuesses(computer_guess_history);

  Codebreaker computer(kSecretCodeLength, kMinSecretCodeDigit,
                       kMaxSecretCodeDigit);
  std::vector<int> computer_guess = {0, 0, 1, 1};

  while (player_computer.GetLife() > 0) {
    computer.RemoveCode(computer_guess); // Remove the guess from the set
    if (computer_guess == player_computer.GetSecretCode()) {
      Congratulations();
      for (const auto &i : player_computer.GetSecretCode()) {
        std::cout << i << " ";
      }
      std::cout << std::endl;
      break;
    }
    std::string feedback =
        GiveFeedback(player_computer.GetSecretCode(), computer_guess);
    player_computer.AddGuess(computer_guess, feedback);
    PrintGuesses(player_computer.GetGuesses());
    player_computer.DecrementLife();
    if (player_computer.GetLife() == 0) {
      TryAgain();
      for (const auto &i : player_computer.GetSecretCode()) {
        std::cout << i << " ";
      }
      std::cout << std::endl;
    }
    computer.PruneCodes(computer_guess, feedback); // Prune the set of codes
    computer_guess = computer.MakeGuess(); // Use MakeGuess to get a guess
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

void Gameplay::CheckGameOver(int &life, const std::string &secret_code) {
  if (--life == 0) {
    TryAgain();
    std::cout << secret_code << std::endl;
  }
}

void Gameplay::PrintGuesses(
    const std::vector<std::pair<std::vector<int>, std::string>> &guesses) {
  Title();
  for (const auto &i : guesses) {
    for (const auto &c : i.first) {
      std::cout << c << " ";
    }
    std::cout << "   " << i.second << std::endl;
  }
}

std::vector<int> Gameplay::InputGuess(const std::string &prompt) {
  std::string input;
  while (true) {
    std::cout << prompt;
    std::cin >> input;

    // `std::string_view` offers better performance with string comparisons
    // by avoiding copying the string
    std::string_view view_input = input;
    if (view_input == "/save") {
      // SaveGame(player);
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
  std::vector<int> result;

  for (char c : input) {
    result.push_back(c - '0');
  }

  return result;
}
