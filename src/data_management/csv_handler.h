#ifndef DATA_MANAGEMENT_CSV_HANDLER_H_
#define DATA_MANAGEMENT_CSV_HANDLER_H_

#include <string>

#include "player/player.h"

class CSVHandler {
public:
  CSVHandler(){};

  CSVHandler(const std::string &file_name);

  void SetFileName(const std::string &file_name);

  void SaveScore(const player::Player &player);

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

#endif // DATA_MANAGEMENT_CSV_HANDLER_H_
