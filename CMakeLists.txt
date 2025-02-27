cmake_minimum_required(VERSION 3.5)
project(text_analysis)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)
set(MAIN_DIR ${CMAKE_SOURCE_DIR}/main)

set(SOURCES
    ${SOURCE_DIR}/prepare_text.cpp
    ${SOURCE_DIR}/process_text.cpp
)

include_directories(${SOURCE_DIR})

add_executable(prepare ${MAIN_DIR}/prepare.cpp ${SOURCES})