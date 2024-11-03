#ifndef LOGGER_LOGGER_H_
#define LOGGER_LOGGER_H_

#include <string>

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

private:
  Logger();
};

#endif // LOGGER_LOGGER_H_
