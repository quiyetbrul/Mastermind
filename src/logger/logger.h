/**
 * @file logger.h
 * @brief Declaration of a logger class.
 */

#ifndef LOGGER_LOGGER_H_
#define LOGGER_LOGGER_H_

#include <fstream>
#include <string>

class Logger {
public:
  /**
   * @brief Get the instance of the Logger class.
   *
   * This function returns the instance of the Logger class.
   *
   * @return Logger& The instance of the Logger class.
   */
  static Logger &GetInstance() {
    static Logger instance;
    return instance;
  }

  /**
   * @brief Delete the copy constructor.
   */
  Logger(const Logger &) = delete;

  /**
   * @brief Delete the assignment operator.
   */
  Logger &operator=(const Logger &) = delete;

  /**
   * @brief Set the output file for logging.
   *
   * @param file_name The name of the output file.
   */
  void SetOutputFile(const std::string &file_name);

  /**
   * @brief Log a message to the output file.
   *
   * This function logs a message to the output file. Each log is prepended with
   * a timestamp.
   *
   * @param message The message to log.
   */
  void Log(const std::string &message);

  /**
   * @brief Close the output file.
   */
  void CloseOutputFile();

private:
  /**
   * @brief Constructor for the Logger class.
   */
  Logger(){};

  std::ofstream output_file_;
  std::string output_file_name_;

  /**
   * @brief Get the current time.
   *
   * This function returns the current time as a string.
   *
   * @return std::string The current time.
   */
  std::string GetCurrentTime() const;

  /**
   * @brief Initialize the Logger.
   */
  void Init();
};

#endif // LOGGER_LOGGER_H_
