set(GAME_STATE_SOURCES
    game_state.cpp
)

add_library(game_state ${GAME_STATE_SOURCES})
target_include_directories(game_state PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(game_state PRIVATE data_management)
