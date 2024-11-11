set(GAME_DATA
    score.cpp
)

add_library(game_data ${GAME_DATA})
target_include_directories(game_data PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(game_data PRIVATE data_management)

include_directories(${SQLite3_INCLUDE_DIRS} ${SQLiteCpp_INCLUDE_DIRS})
target_link_libraries(game_data PUBLIC ${SQLite3_LIBRARIES} SQLiteCpp)
