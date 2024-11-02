#ifndef PLAYER_COMPUTER_CODEBREAKER_H_
#define PLAYER_COMPUTER_CODEBREAKER_H_

#include <map>
#include <string>
#include <vector>

namespace player {
// TODO: Optimize the codebreaker algorithm
class Codebreaker {
public:
  // Constructor
  Codebreaker(int code_length, int min_digit, int max_digit);

  // Generate initial guess
  std::vector<int> MakeGuess();

  void RemoveCode(const std::vector<int> &guess);
  void PruneCodes(const std::vector<int> &guess, const std::string &feedback);

private:
  const int code_length_;
  const int min_digit_;
  const int max_digit_;

  std::vector<std::vector<int>> combinations_;
  std::vector<std::vector<int>> candidate_solutions_;

  void CreateSet();
  void GenerateCombinations(int position, std::vector<int> &current);
  void RemoveCode(std::vector<std::vector<int>> &set,
                  const std::vector<int> &guess);
  void FilterSolutions(const std::vector<int> &guess,
                       const std::string &feedback);
  std::vector<std::vector<int>> Minimax();
  int GetMaxScore(const std::map<std::string, int> &score_count);
  int GetMinScore(const std::map<std::vector<int>, int> &score);
};
} // namespace player
#endif // PLAYER_COMPUTER_CODEBREAKER_H_
