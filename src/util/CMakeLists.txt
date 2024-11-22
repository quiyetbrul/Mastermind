set(UTIL_SOURCES
    input_validation.cpp
    random_integers.cpp
    util_os.cpp
)

add_library(util ${UTIL_SOURCES})
target_include_directories(util PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_include_directories(util PUBLIC ${CURSES_INCLUDE_DIR})
target_link_libraries(util PUBLIC ${CURSES_LIBRARIES})

# TESTS
# Add test executables
add_executable(util_test input_validation_test.cpp)
add_executable(util_mock random_integers_test.cpp)

# Link test executables to required libraries
target_link_libraries(util_test PUBLIC ${GTEST_LIBRARIES} ${CURL_LIBRARIES} util logger)
target_link_libraries(util_mock PUBLIC ${GTEST_LIBRARIES} ${CURL_LIBRARIES} util logger)

# Discover and register tests
include(GoogleTest)
gtest_discover_tests(util_test)
gtest_discover_tests(util_mock)

