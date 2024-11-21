set(UTIL_SOURCES
    input_validation.cpp
    random_integers.cpp
    util_os.cpp
)

add_library(util ${UTIL_SOURCES})
target_include_directories(util PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(util PUBLIC ${CURSES_LIBRARIES})

# TESTS
find_package(GTest REQUIRED)
find_package(CURL REQUIRED)

add_executable(util_test
    input_validation_test.cpp
    random_integers_test.cpp
    util_test.cpp
)

target_include_directories(util_test PUBLIC ${CURL_INCLUDE_DIRS})
target_link_libraries(util_test PUBLIC ${GTEST_LIBRARIES} ${CURL_LIBRARIES} util logger)
