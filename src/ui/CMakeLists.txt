set(UI_SOURCES
    menu.cpp
)

add_library(ui ${UI_SOURCES})
target_include_directories(ui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
