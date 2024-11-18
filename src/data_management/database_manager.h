/**
 * @file database_manager.cpp
 * @brief Abstract class declaration for database manager
 */

#ifndef DATA_MANAGEMENT_DATABASE_MANAGER_H_
#define DATA_MANAGEMENT_DATABASE_MANAGER_H_

#include <string>

#include "logger/logger.h"

namespace data_management {
/**
 * @class DatabaseHandler
 * @brief Represents a database manager.
 *
 * The DatabaseHandler class is an abstract class that manages the database
 * operations.
 */
class DatabaseManager {
public:
  /**
   * @brief Construct a new Database Handler object
   */
  DatabaseManager(){};

  /**
   * @brief Virtual destructor.
   */
  virtual ~DatabaseManager() = default;

  // GETTERS

  std::string GetTableName() const { return table_name_; }

protected:
  Logger &logger_ = Logger::GetInstance();

  /**
   * @brief Creates the table in the database.
   */
  virtual void CreateTable(const std::string &table_name) = 0;

  // SETTERS

  void SetTableName(const std::string &table_name) { table_name_ = table_name; }

private:
  std::string table_name_;
};
} // namespace data_management
#endif // DATA_MANAGEMENT_DATABASE_MANAGER_H_
