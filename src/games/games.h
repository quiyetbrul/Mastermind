#ifndef GAMES_GAMES_H_
#define GAMES_GAMES_H_

#include <string>

#include "player/player.h"

class Games {
public:
  Games(){};

  Games(std::string game_name_, std::string game_password_,
        const player::Player &player_)
      : game_name_(game_name_), game_password_(game_password_),
        player_(player_) {}

  // getters
  std::string GetGameName() const;
  std::string GetGamePassword() const;
  player::Player GetPlayer() const;

  // setters
  void SetGameName(const std::string &game_name);
  void SetGamePassword(const std::string &game_password);

private:
  std::string game_name_;
  std::string game_password_;
  player::Player player_;
};

#endif // GAMES_GAMES_H_
