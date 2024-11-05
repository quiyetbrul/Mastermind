#ifndef LOGGER_LOGGER_H_
#define LOGGER_LOGGER_H_

#include <string>
#include <fstream>

class Logger {
public:
  static Logger &GetInstance() {
    static Logger instance;
    return instance;
  }

  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;

  void SetOutputFile(const std::string &file_name);
  void Log(const std::string &message);
  void CloseOutputFile();

private:
  Logger(){};

  std::ofstream output_file_;
  std::string output_file_name_;

  std::string GetCurrentTime() const;
  void Init();
};

#endif // LOGGER_LOGGER_H_
