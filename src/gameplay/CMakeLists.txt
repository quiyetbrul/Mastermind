set(GAMEPLAY_SOURCES
    gameplay.cpp
)

add_library(gameplay ${GAMEPLAY_SOURCES})
target_include_directories(gameplay PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
