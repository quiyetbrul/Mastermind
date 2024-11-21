set(PLAYER_SOURCES
    player.cpp
    util/util.cpp

    type/codemaster/codebreaker/codebreaker.cpp
    type/codemaster/codemaster.cpp
    type/single/single.cpp
)

add_library(player ${PLAYER_SOURCES})
target_include_directories(player PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(player PRIVATE data_management)

target_include_directories(player PUBLIC ${CURSES_INCLUDE_DIR})
target_link_libraries(player PUBLIC ${CURSES_LIBRARIES})
