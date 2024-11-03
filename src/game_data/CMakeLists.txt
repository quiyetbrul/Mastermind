set(GAME_DATA_SOURCES
    saved_games/saved_games.cpp
    scoreboard/scoreboard.cpp
)

add_library(game_data STATIC ${GAME_DATA_SOURCES})

target_include_directories(game_data PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_compile_definitions(game_data PRIVATE -DSCORES_FILE_PATH=\"${CMAKE_BINARY_DIR}/src/data/scoreboard.csv\")
target_compile_definitions(game_data PRIVATE -DSAVED_GAMES_FILE_PATH=\"${CMAKE_BINARY_DIR}/src/data/one_players.json\")
