set(LOGGER_SOURCES
    logger.cpp
)

add_library(logger ${LOGGER_SOURCES})

target_include_directories(logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

# TESTS
add_executable(logger_test
    logger_test.cpp
)

target_link_libraries(logger_test ${GTEST_LIBRARIES} logger)

include(GoogleTest)
gtest_discover_tests(logger_test)
