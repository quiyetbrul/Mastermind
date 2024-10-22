#ifndef CSV_HANDLER_H_
#define CSV_HANDLER_H_

#include <string>

#include "player/player.h"

class CSVHandler {
public:
  CSVHandler(){};

  CSVHandler(const std::string &file_name);

  void SetFileName(const std::string &file_name);

  void SaveScore(const Player &player);

  std::vector<std::pair<std::string, int>> GetScores() const;

  void PrintScores() const;

  bool IsHighScore(const int &score) const;

  private:
    std::string file_name_;
    static std::vector<std::pair<std::string, int>> saved_scores_;
    const int kScoreLimit = 10;

    void UpdateScoreboard();
    void AddScore(const std::string &name, const int &score);
  };

#endif // CSV_HANDLER_H_
