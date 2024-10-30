# Define the source files for the game_data library
set(GAME_DATA_SOURCES
    scoreboard/scoreboard.cpp
)

# Add the game_data library
add_library(game_data ${GAME_DATA_SOURCES})

# Specify the include directories for the game_data library
target_include_directories(game_data PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

# Define the SCORES_FILE_PATH macro for the game_data target
target_compile_definitions(game_data PRIVATE SCORES_FILE_PATH=\"${CMAKE_SOURCE_DIR}/src/data/scoreboard.csv\")
