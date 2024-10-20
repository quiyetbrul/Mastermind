#ifndef CODEBREAKER_H_
#define CODEBREAKER_H_

#include <map>
#include <string>
#include <vector>

class Codebreaker {
public:
  // Constructor
  Codebreaker(int code_length, int min_digit, int max_digit);

  // Generate initial guess
  std::vector<int> MakeGuess();

  void removeCode(const std::vector<int> &guess);
  void pruneCodes(const std::vector<int> &guess, const std::string &feedback);
  std::vector<std::vector<int>> minimax();

private:
  const int code_length_;
  int min_digit_;
  int max_digit_;

  std::vector<std::vector<int>> combinations_;
  std::vector<std::vector<int>> candidate_solutions_;

  void createSet();
  void generateCombinations(int position, std::vector<int> &current);
  std::string checkCode(std::vector<int> guess, std::vector<int> secret_code);

  int getMaxScore(const std::map<std::string, int> &score_count);
  int getMinScore(const std::map<std::vector<int>, int> &score);
};

#endif // CODEBREAKER_H_
