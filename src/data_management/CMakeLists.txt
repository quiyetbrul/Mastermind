set(DATA_HANDLER
    scoreboard/scoreboard_handler.cpp
    scoreboard/scoreboard.cpp
    saved_games/saved_games_handler.cpp
    saved_games/saved_games.cpp
)

add_library(data_management ${DATA_HANDLER})
target_include_directories(data_management PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_compile_definitions(data_management PRIVATE -DSCORES_FILE_PATH=\"${CMAKE_BINARY_DIR}/src/data/scoreboard.csv\")
target_compile_definitions(data_management PRIVATE -DSAVED_GAMES_FILE_PATH=\"${CMAKE_BINARY_DIR}/src/data/quick_game.json\")

target_link_libraries(data_management PRIVATE nlohmann_json::nlohmann_json)
