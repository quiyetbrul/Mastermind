/**
 * @file database_handler.cpp
 * @brief Abstract class declaration for database handler
 */

#ifndef DATA_MANAGEMENT_DATABASE_MANAGER_H_
#define DATA_MANAGEMENT_DATABASE_MANAGER_H_

#include <string>

#include "logger/logger.h"

namespace data_management {
/**
 * @class DatabaseHandler
 * @brief Represents a database handler.
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

  // /**
  //  * @brief Inserts a record into the database.
  //  */
  // virtual void InsertRecord(const std::vector<std::string> &values) = 0;

  // /**
  //  * @brief Queries records from the database.
  //  */
  // virtual void QueryRecords() = 0;

  // /**
  //  * @brief Updates a record in the database.
  //  */
  // virtual void UpdateRecord(const int &id,
  //                           std::vector<std::string> &values) = 0;

  // /**
  //  * @brief Deletes a record from the database.
  //  */
  // virtual void DeleteRecord(const int &id) = 0;

protected:
  Logger &logger_ = Logger::GetInstance();

  /**
   * @brief Creates the table in the database.
   */
  virtual void CreateTable(const std::string &table_name) = 0;

  // GETTERS

  std::string GetTableName() const { return table_name_; }

  // SETTERS

  void SetTableName(const std::string &table_name) { table_name_ = table_name; }

private:
  std::string table_name_;
};
} // namespace data_management
#endif // DATA_MANAGEMENT_DATABASE_MANAGER_H_
