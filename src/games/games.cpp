#include "games.h"
#include <string>

std::string Games::GetGameName() const { return game_name_; }

std::string Games::GetGamePassword() const { return game_password_; }

Player Games::GetPlayer() const { return player_; }

void Games::SetGameName(const std::string &game_name) {
  game_name_ = game_name;
}

void Games::SetGamePassword(const std::string &game_password) {
  game_password_ = game_password;
}
