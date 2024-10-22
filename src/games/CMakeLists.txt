set(GAMES_SOURCES
    games.cpp
)

add_library(games ${GAMES_SOURCES})
target_include_directories(games PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
