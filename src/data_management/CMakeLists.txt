set(CSV_HANDLER_SOURCES
    csv_handler.cpp
    json_handler.cpp
)

add_library(data_management ${CSV_HANDLER_SOURCES})
target_include_directories(data_management PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
