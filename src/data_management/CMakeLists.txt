set(DATA_HANDLER
    database_manager.h
    scoreboard/score.cpp
    scoreboard/scoreboard.cpp
    saved_games/game.cpp
    saved_games/saved_games.cpp
)

add_library(data_management ${DATA_HANDLER})
target_include_directories(data_management PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(data_management PRIVATE logger)

include_directories(${SQLite3_INCLUDE_DIRS} ${SQLiteCpp_INCLUDE_DIRS})
target_link_libraries(data_management PUBLIC ${SQLite3_LIBRARIES} SQLiteCpp)

target_link_libraries(data_management PUBLIC nlohmann_json::nlohmann_json)

include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(data_management PUBLIC ${CURSES_LIBRARIES})
