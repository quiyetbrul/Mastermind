set(LOGGER_SOURCES
    logger.cpp
)

add_library(logger ${LOGGER_SOURCES})

target_include_directories(logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

# TESTS
find_package(GTest REQUIRED)

add_executable(logger_test
    logger_test.cpp
)

target_include_directories(logger_test PUBLIC ${GTEST_INCLUDE_DIRS} ${CURL_INCLUDE_DIRS})
target_link_libraries(logger_test ${GTEST_LIBRARIES} logger)
