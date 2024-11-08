/**
 * @file saved_games_handler.cpp
 * @brief Implementation of the SavedGamesHandler class
 */

#include "saved_games_handler.h"

#include <fstream>

#include <nlohmann/json.hpp>

namespace data_management {

void SavedGamesHandler::Init() {
  logger_.Log("Initializing saved games handler");
  if (file_name_.empty()) {
    logger_.Log("Initialize: file_name_ is empty");
    return;
  }

  std::ifstream file(file_name_);
  if (!file.is_open()) {
    logger_.Log("Failed to open: " + file_name_);
    logger_.Log("Error: " + std::string(strerror(errno)));

    // Create the necessary directories and file
    std::filesystem::create_directories(
        std::filesystem::path(file_name_).parent_path());
    logger_.Log("Creating: " + file_name_);
    std::ofstream create_file(file_name_);
    if (!create_file.is_open()) {
      logger_.Log("Failed to create: " + file_name_);
      logger_.Log("Error: " + std::string(strerror(errno)));
    } else {
      create_file.close();
      logger_.Log("Successfully created: " + file_name_);
    }
  } else {
    file.close();
  }
}

std::unordered_map<std::string, game_type::QuickGame>
SavedGamesHandler::GetSavedGames() const {
  std::unordered_map<std::string, game_type::QuickGame> saved_games;

  return saved_games;
}

void SavedGamesHandler::SaveGame(
    const std::unordered_map<std::string, game_type::QuickGame> &players) {}

void SavedGamesHandler::DeleteGame(const std::string &game_name_to_delete) {}
} // namespace data_management
