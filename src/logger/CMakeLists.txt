set(LOGGER_SOURCES
    logger.cpp
)

add_library(logger ${LOGGER_SOURCES})

target_include_directories(logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
