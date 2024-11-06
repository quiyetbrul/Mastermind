set(PLAYER_SOURCES
    player.cpp
    single/single.cpp
    util/util.cpp
)

add_library(player ${PLAYER_SOURCES})
target_include_directories(player PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(player PRIVATE data_management)
