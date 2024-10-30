set(DATA_HANDLER
    scoreboard_handler.cpp
    json_handler.cpp
)

add_library(data_management ${DATA_HANDLER})
target_include_directories(data_management PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
