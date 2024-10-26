#include "single_player.h"

#include "data_management/csv_handler.h"
#include "gameplay/util/gameplay_util.h"
#include "ui/print.h"
#include "util/util.h"

void SinglePlayer::Start() {
  Title();

  std::vector<std::pair<std::vector<int>, std::string>> user_guess_history;
  player.SetSecretCode(
      GenRandom(kSecretCodeLength, kMinSecretCodeDigit, kMaxSecretCodeDigit));
  player.SetGuesses(user_guess_history);

  PlayGameLoop(player);
  if (player.IsWinner()) {
    CSVHandler csv_handler("src/data_management/data/scoreboard.csv");
    if (csv_handler.IsHighScore(player.GetScore())) {
      std::string player_name = InputString("Highscore! Enter your name: ");
      player.SetScore(player.GetLife());
      player.SetName(player_name);
      csv_handler.SaveScore(player);
      csv_handler.PrintScores();
    }
  }
}
