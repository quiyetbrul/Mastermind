set(GAME_DATA_SOURCES
    scoreboard/scoreboard.cpp
    saved_games/saved_games.cpp
)

add_library(game_data ${GAME_DATA_SOURCES})

target_include_directories(game_data PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_compile_definitions(game_data PRIVATE -DSCORES_FILE_PATH=\"${CMAKE_BINARY_DIR}/src/data/scoreboard.csv\")
target_compile_definitions(game_data PRIVATE -DSAVED_GAMES_FILE_PATH=\"${CMAKE_BINARY_DIR}/src/data/one_players.json\")
