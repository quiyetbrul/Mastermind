set(PLAYER_SOURCES
    player.cpp
)

add_library(player ${PLAYER_SOURCES})
target_include_directories(player PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
