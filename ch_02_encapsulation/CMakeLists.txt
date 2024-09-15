cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# set the project name and version
# NOTE: `project` automatically defines `PROJECT_NAME` and `PROJECT_SOURSE_DIR`
project(ch_02 CXX)

set(PROJECT_VERSION 1.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add subdirectory
#set(SOURCE_FILES
#    simple_mc_main_1.cpp
#    )

#set(HEADER_FILES
#    random_1.h
#    )

file(GLOB_RECURSE SOURCES "./src/*.cpp" "./src/*.h")

# Generate executable
add_executable(ch_02
    ${SOURCES}
    )

target_include_directories(ch_02
    PUBLIC
    ${PROJECT_SOURCE_DIR}
    )

# Setting up the startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ch_02)
