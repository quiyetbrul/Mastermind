#ifndef CODEBREAKER_H_
#define CODEBREAKER_H_

#include <string>
#include <unordered_map>
#include <vector>

class Codebreaker {
public:
  Codebreaker(const int &code_length, const int &min_digit,
              const int &max_digit);

  std::string MakeGuess();

  void ReceiveFeedback(const std::string &feedback);

private:
  int code_length_;
  int min_digit_;
  int max_digit_;
  std::vector<std::string> possible_guesses_;
  std::string current_guess_;
  std::unordered_map<char, int> correct_position_;
  std::unordered_map<char, int> correct_digit_;

  // Helper functions
  void GenerateAllGuesses();
  void FilterGuessesBasedOnFeedback(const std::string &feedback);
};

#endif // CODEBREAKER_H_
