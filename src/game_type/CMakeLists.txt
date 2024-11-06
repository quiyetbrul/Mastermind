set(GAME_TYPE_SOURCES
    codemaster/codebreaker/codebreaker.cpp
    codemaster/codemaster.cpp
)

add_library(game_type ${GAME_TYPE_SOURCES})
target_include_directories(game_type PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(game_type PRIVATE data_management)
