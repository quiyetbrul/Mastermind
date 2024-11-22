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
add_executable(input_validation input_validation_test.cpp)
# add_executable(random_integers random_integers_test.cpp)

target_link_libraries(input_validation PUBLIC ${GTEST_LIBRARIES} ${CURL_LIBRARIES} util logger)
# target_link_libraries(random_integers PUBLIC ${GTEST_LIBRARIES} ${CURL_LIBRARIES} util logger)

include(GoogleTest)
gtest_discover_tests(input_validation)
# gtest_discover_tests(random_integers)

