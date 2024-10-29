set(GAMEPLAY_SOURCES
    gameplay.cpp
    util/gameplay_util.cpp
)

add_library(gameplay ${GAMEPLAY_SOURCES})
target_include_directories(gameplay PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
