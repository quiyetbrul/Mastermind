set(PLAYER_SOURCES
    player.cpp
    util/util.cpp

    type/codemaster/codebreaker/codebreaker.cpp
    type/codemaster/codemaster.cpp
    type/one_player/one_player.cpp
    type/timed/timed.cpp
    )

add_library(player ${PLAYER_SOURCES})
target_include_directories(player PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(player PRIVATE data_management)

include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(player PUBLIC ${CURSES_LIBRARIES})
