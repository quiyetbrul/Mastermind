set(GAMEPLAY_SOURCES
    gameplay.cpp
    codebreaker/codebreaker.cpp
    computer_player/computer_player.cpp
    human_player/single_player/single_player.cpp
    util/gameplay_util.cpp
)

add_library(gameplay ${GAMEPLAY_SOURCES})
target_include_directories(gameplay PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
