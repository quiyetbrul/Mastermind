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
find_package(GTest REQUIRED)
find_package(CURL REQUIRED)

include(GoogleTest)

add_executable(util_test
    input_validation_test.cpp
)
target_include_directories( util_test PUBLIC ${GTEST_INCLUDE_DIRS} ${CURL_INCLUDE_DIRS})
target_link_libraries( util_test PUBLIC ${GTEST_LIBRARIES} ${CURL_LIBRARIES} util logger)

# add_executable(util_mock
#     random_integers_test.cpp
# )
# target_include_directories(util_mock PUBLIC ${GTEST_INCLUDE_DIRS} ${CURL_INCLUDE_DIRS})
# target_link_libraries(util_mock PUBLIC ${GTEST_LIBRARIES} ${CURL_LIBRARIES} util logger)

gtest_discover_tests(util_test)
# gtest_discover_tests(util_mock)
