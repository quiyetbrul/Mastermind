/**
 * @file database_manager.cpp
 * @brief Abstract class declaration for database manager
 */

#ifndef DATA_MANAGEMENT_DATABASE_MANAGER_H_
#define DATA_MANAGEMENT_DATABASE_MANAGER_H_

#include <string>

#include "logger/logger.h"

#include <SQLiteCpp/SQLiteCpp.h>
#include <ncurses.h>

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
  DatabaseManager()
      : db_(MASTERMIND_DB_PATH, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE){};

  /**
   * @brief Virtual destructor.
   */
  virtual ~DatabaseManager() = default;

  // GETTERS

  WINDOW *GetWindow() const { return window_; }
  std::string GetTableName() const { return table_name_; }
  int GetCount() const {
    SQLite::Statement query(db_, "SELECT COUNT(*) FROM " + GetTableName());
    query.executeStep();
    return query.getColumn(0).getInt();
  }
  int GetCount(const std::string &game_name) const {
    SQLite::Statement query(db_, "SELECT COUNT(*) FROM " + GetTableName() +
                                     " WHERE GAME_NAME = ?");
    query.bind(1, game_name);
    query.executeStep();
    return query.getColumn(0).getInt();
  }

  // SETTERS

  void SetWindow(WINDOW *window) { window_ = window; }
  void SetTableName(const std::string &table_name) { table_name_ = table_name; }

protected:
  Logger &logger_ = Logger::GetInstance();
  SQLite::Database db_;

  /**
   * @brief Creates the table in the database.
   */
  virtual void CreateTable(const std::string &table_name) = 0;

private:
  WINDOW *window_;
  std::string table_name_;
};
} // namespace data_management
#endif // DATA_MANAGEMENT_DATABASE_MANAGER_H_
