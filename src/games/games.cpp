#include "games.h"
#include <string>

std::string Games::GetGameName() const { return game_name_; }

std::string Games::GetGamePassword() const { return game_password_; }

int Games::GetPlayerOneLife() const { return player_one_life_; }

int Games::GetPlayerOneScore() const { return player_one_score_; }

std::string Games::GetPlayerOneSecretCode() const {
  return player_one_secret_code_;
}

std::vector<std::pair<std::string, std::string>>
Games::GetPlayerOneGuesses() const {
  return player_one_guesses_;
}

void Games::SetGameName(const std::string &game_name) {
  game_name_ = game_name;
}

void Games::SetGamePassword(const std::string &game_password) {
  game_password_ = game_password;
}

void Games::SetPlayerOneLife(const int &player_one_life) {
  player_one_life_ = player_one_life;
}

void Games::SetPlayerOneScore(const int &player_one_score) {
  player_one_score_ = player_one_score;
}

void Games::SetPlayerOneSecretCode(const std::string &player_one_secret_code) {
  player_one_secret_code_ = player_one_secret_code;
}

void Games::SetPlayerOneGuesses(
    const std::vector<std::pair<std::string, std::string>>
        &player_one_guesses) {
  player_one_guesses_ = player_one_guesses;
}
