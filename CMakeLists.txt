cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(mastermind)

# Add the include directory for jsoncpp
# Change this to the location of your jsoncpp installation
include_directories(/opt/homebrew/opt/jsoncpp/include)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Enable debug symbols by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug
        CACHE STRING
            "Choose the type of build (Debug or Release)" FORCE)
endif()

# Export compile commands for completion engines (optional)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME}
                                src/main.cpp
                                src/gameplay/gameplay.cpp
                                src/ui/menu.cpp
                                src/util/util.cpp
                                src/util/util_os.cpp
                                )

# Find and link libcurl
find_package(CURL REQUIRED)
target_include_directories(mastermind PRIVATE ${CURL_INCLUDE_DIRS})
target_link_libraries(mastermind PRIVATE ${CURL_LIBRARIES})

# Using INSTALL_RPATH_USE_LINK_PATH
set_target_properties(${PROJECT_NAME}
    PROPERTIES
        INSTALL_RPATH_USE_LINK_PATH TRUE)

# Set executable RPATH
set_target_properties(${PROJECT_NAME}
    PROPERTIES
        INSTALL_RPATH
            "${CMAKE_INSTALL_PREFIX}/lib"
)

# Set executable install location
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# Set install location for resources
install(DIRECTORY assets
    DESTINATION "${CMAKE_INSTALL_PREFIX}/share/${CMAKE_PROJECT_NAME}"
)
