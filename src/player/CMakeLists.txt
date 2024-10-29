set(PLAYER_SOURCES
    player.cpp
    computer_player/codebreaker/codebreaker.cpp
    computer_player/computer_player.cpp
    single_player/single_player.cpp
)

add_library(player ${PLAYER_SOURCES})
target_include_directories(player PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
