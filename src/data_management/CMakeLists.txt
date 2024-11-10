set(DATA_HANDLER
    scoreboard.cpp
    saved_games.cpp
)

add_library(data_management ${DATA_HANDLER})
target_include_directories(data_management PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(data_management PRIVATE logger)

target_compile_definitions(data_management PRIVATE -DMASTERMIND_DATA=\"${CMAKE_BINARY_DIR}/src/data/mastermind.db\")

include_directories(${SQLite3_INCLUDE_DIRS} ${SQLiteCpp_INCLUDE_DIRS})
target_link_libraries(data_management PUBLIC ${SQLite3_LIBRARIES} SQLiteCpp)

target_link_libraries(data_management PUBLIC nlohmann_json::nlohmann_json)
