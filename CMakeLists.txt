cmake_minimum_required(VERSION 3.10)
project(Laba03Ver2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Найти все cpp файлы и добавить их в проект
file(GLOB SOURCES "*.cpp")
add_executable(laba03ver2 ${SOURCES})

option(ENABLE_DEBUG "Enable debug mode" FALSE)

if(ENABLE_DEBUG)
    set(CMAKE_BUILD_TYPE Debug)
    add_compile_definitions(DEBUG)
    message(STATUS "Debug mode enabled")
endif()
