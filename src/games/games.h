#ifndef GAMES_H_
#define GAMES_H_

#include <string>
#include <vector>

#include "../player/player.h"

class Games {
public:
  Games(){};

  Games(std::string game_name_, std::string game_password_,
        const Player &player)
      : game_name_(game_name_), game_password_(game_password_) {}

  Games(std::string game_name_, std::string game_password_, int player_one_life,
        int player_one_score_, std::string player_one_secret_code_,
        std::vector<std::pair<std::string, std::string>> player_one_guesses_)
      : game_name_(game_name_), game_password_(game_password_),
        player_one_life_(player_one_life), player_one_score_(player_one_score_),
        player_one_secret_code_(player_one_secret_code_),
        player_one_guesses_(player_one_guesses_) {}

  // getters
  std::string GetGameSaveTime() const;
  std::string GetGameName() const;
  std::string GetGamePassword() const;
  int GetPlayerOneLife() const;
  int GetPlayerOneScore() const;
  std::string GetPlayerOneSecretCode() const;
  std::vector<std::pair<std::string, std::string>> GetPlayerOneGuesses() const;

  // setters
  void SetGameSaveTime(const std::string &game_save_time);
  void SetGameName(const std::string &game_name);
  void SetGamePassword(const std::string &game_password);
  void SetPlayerOneLife(const int &player_one_life);
  void SetPlayerOneScore(const int &player_one_score);
  void SetPlayerOneSecretCode(const std::string &player_one_secret_code);
  void
  SetPlayerOneGuesses(const std::vector<std::pair<std::string, std::string>>
                          &player_one_guesses);

private:
  std::string game_name_;
  std::string game_password_;

  int player_one_life_ = 0;
  int player_one_score_ = 0;
  // TODO: turn into array instead of vector
  std::vector<std::pair<std::string, std::string>> player_one_guesses_;
  std::string player_one_secret_code_;
};

#endif // GAMES_H_
