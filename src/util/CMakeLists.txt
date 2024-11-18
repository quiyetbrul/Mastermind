set(UTIL_SOURCES
    input_validation.cpp
    random_integers.cpp
    util_os.cpp
)

add_library(util ${UTIL_SOURCES})
target_include_directories(util PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(util PUBLIC ${CURSES_LIBRARIES})
