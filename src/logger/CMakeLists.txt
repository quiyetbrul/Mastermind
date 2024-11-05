set(LOGGER_SOURCES
    logger.cpp
)

add_library(logger ${LOGGER_SOURCES})

target_include_directories(logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_compile_definitions(logger PUBLIC -DLOGGER_FILE_PATH=\"${CMAKE_BINARY_DIR}/src/data/logger.txt\")
