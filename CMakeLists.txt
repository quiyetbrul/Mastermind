cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(mastermind)

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

# Include subdirectories
add_subdirectory(src/data_management)
add_subdirectory(src/gameplay)
add_subdirectory(src/game_data)
add_subdirectory(src/games)
add_subdirectory(src/player)
add_subdirectory(src/ui)
add_subdirectory(src/util)

# Add executable
add_executable(${PROJECT_NAME} src/main.cpp)

# Link subdirectory libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    data_management
    gameplay
    game_data
    games
    player
    ui
    util
)

# Fetch and link libcurl
# Check if libcurl is available on the system
find_package(CURL QUIET)

if(NOT CURL_FOUND)
    message(STATUS "libcurl not found, fetching libcurl")
    include(FetchContent)

    FetchContent_Declare(
        curl
        GIT_REPOSITORY https://github.com/curl/curl.git
        GIT_TAG curl-7_80_0
    )

    # Prevent building the curl executable
    set(BUILD_CURL_EXE OFF CACHE BOOL "Do not build the curl executable")

    # Make curl available
    FetchContent_MakeAvailable(curl)

    # Include directories and link the libraries
    target_include_directories(${PROJECT_NAME} PRIVATE ${curl_SOURCE_DIR})
    target_link_libraries(${PROJECT_NAME} PRIVATE curl)
else()
    message(STATUS "libcurl found: ${CURL_INCLUDE_DIRS}")
    # Use the system-installed libcurl
    target_include_directories(${PROJECT_NAME} PRIVATE ${CURL_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${CURL_LIBRARIES})
endif()

# Using INSTALL_RPATH_USE_LINK_PATH
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)

# Set executable RPATH
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# Set executable install location
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# Set install location for resources
install(DIRECTORY assets DESTINATION "${CMAKE_INSTALL_PREFIX}/share/${CMAKE_PROJECT_NAME}")
