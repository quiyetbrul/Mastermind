set(LOAD_GAME
    load_game.cpp
)

add_library(load_game ${LOAD_GAME})
target_include_directories(load_game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(load_game PRIVATE data_management)

include_directories(${SQLite3_INCLUDE_DIRS} ${SQLiteCpp_INCLUDE_DIRS})
target_link_libraries(load_game PUBLIC ${SQLite3_LIBRARIES} SQLiteCpp)

target_link_libraries(load_game PUBLIC nlohmann_json::nlohmann_json)

include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(load_game PUBLIC ${CURSES_LIBRARIES})
