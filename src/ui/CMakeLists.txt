set(UI_SOURCES
    banner.cpp
    menu.cpp
)

add_library(ui ${UI_SOURCES})
target_include_directories(ui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_include_directories(ui PUBLIC ${CURSES_INCLUDE_DIR})
target_link_libraries(ui PUBLIC ${CURSES_LIBRARIES})
