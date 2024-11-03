cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(Mastermind)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Enable debug symbols by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# Export compile commands for completion engines (optional)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find 3P libraries
find_package(CURL REQUIRED)

# Include subdirectories
add_subdirectory(src/data_management)
add_subdirectory(src/game_data)
add_subdirectory(src/game_state)
add_subdirectory(src/logger)
add_subdirectory(src/player)
add_subdirectory(src/ui)
add_subdirectory(src/util)

# Add executable
add_executable(${PROJECT_NAME} src/main.cpp)

# Link subdirectory libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    data_management
    game_data
    game_state
    logger
    player
    ui
    util
)

# Link 3P libraries
target_include_directories(${PROJECT_NAME} PRIVATE ${CURL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${CURL_LIBRARIES})

# Using INSTALL_RPATH_USE_LINK_PATH
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)

# Set executable install location
install(TARGETS ${PROJECT_NAME} DESTINATION build)
