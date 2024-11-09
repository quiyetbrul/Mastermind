/**
 * @file database_handler.cpp
 * @brief Abstract class declaration for database handler
 */

#include <string>
#include <vector>

#include "logger/logger.h"

namespace data_management {
/**
 * @class DatabaseHandler
 * @brief Represents a database handler.
 *
 * The DatabaseHandler class is an abstract class that manages the database
 * operations.
 */
class DatabaseHandler {
public:
  /**
   * @brief Construct a new Database Handler object
   */
  DatabaseHandler(){};

  /**
   * @brief Virtual destructor.
   */
  virtual ~DatabaseHandler() = default;

  /**
   * @brief Creates the table in the database.
   */
  virtual void CreateTable(const std::string &table_name) = 0;

  /**
   * @brief Inserts a record into the database.
   */
  virtual void InsertRecord(const std::vector<std::string> &values) = 0;

  /**
   * @brief Queries records from the database.
   */
  virtual void QueryRecords() = 0;

  /**
   * @brief Updates a record in the database.
   */
  virtual void UpdateRecord(const int &id) = 0;

  /**
   * @brief Deletes a record from the database.
   */
  virtual void DeleteRecord(const int &id) = 0;

protected:
  Logger &logger_ = Logger::GetInstance();

  /**
   * @brief Connects to the database.
   */
  void Connect();

  /**
   * @brief Disconnects from the database.
   */
  void Disconnect();
};
} // namespace data_management
