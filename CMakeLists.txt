cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(Mastermind)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_MESSAGE_LOG_LEVEL ERROR)

# Enable debug symbols by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# Export compile commands for completion engines (optional)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find 3P libraries
find_package(CURL REQUIRED)
find_package(SQLiteCpp REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(Curses REQUIRED)
find_package(GTest REQUIRED)

enable_testing()

# Definitions
add_definitions(-DMASTERMIND_DB_PATH=\"${CMAKE_BINARY_DIR}/src/data/mastermind.db\")
add_definitions(-DLOGGER_FILE_PATH=\"${CMAKE_BINARY_DIR}/src/data/logger.txt\")
add_definitions(-DLOGGER_TEST_FILE_PATH=\"${CMAKE_BINARY_DIR}/src/data/logger_test_file.txt\")

# Include subdirectories
add_subdirectory(src/data_management)
add_subdirectory(src/game_state)
add_subdirectory(src/load_game)
add_subdirectory(src/logger)
add_subdirectory(src/player)
add_subdirectory(src/ui)
add_subdirectory(src/util)

# Add executable
add_executable(${PROJECT_NAME} src/main.cpp)

# Link subdirectory libraries
target_link_libraries(${PROJECT_NAME} PUBLIC
    data_management
    game_state
    load_game
    player
    ui
    util
)

# Link 3P libraries
target_include_directories(${PROJECT_NAME} PUBLIC ${CURL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${CURL_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC ${SQLite3_INCLUDE_DIRS} ${SQLiteCpp_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json::nlohmann_json)

target_include_directories(${PROJECT_NAME} PUBLIC ${CURSES_INCLUDE_DIR})

# Using INSTALL_RPATH_USE_LINK_PATH
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)

# Set executable install location
install(TARGETS ${PROJECT_NAME} DESTINATION build)
