#ifndef GAMES_H_
#define GAMES_H_

#include <string>
#include <vector>

class Games {
public:
  Games();

  // Single player constructor
  Games(int player_one_life, int player_one_score_,
        std::string player_one_secret_code,
        std::vector<std::pair<std::string, std::string>> player_one_guesses_);

  // Multiplayer constructor
    Games(int player_one_life, int player_one_score_,
            std::string player_one_secret_code,
            std::vector<std::pair<std::string, std::string>> player_one_guesses_,
            int player_two_life, int player_two_score_,
            std::string player_two_secret_code,
            std::vector<std::pair<std::string, std::string>> player_two_guesses_);

private:
  std::string player_one_name_;
  std::string player_one_password_;
  int player_one_life_ = 0;
  int player_one_score_ = 0;
  std::vector<std::pair<std::string, std::string>> player_one_guesses_;
  std::string player_one_secret_code_;

  std::string player_two_name_;
  std::string player_two_password_;
  int player_two_life_ = 0;
  int player_two_score_ = 0;
  std::vector<std::pair<std::string, std::string>> player_two_guesses_;
  std::string player_two_secret_code_;

  // TODO: getters/setters
};

#endif // GAMES_H_
