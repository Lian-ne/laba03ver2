cmake_minimum_required(VERSION 3.10)
project(lab3)

# Устанавливаем стандарт C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Флаги компилятора
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic")

# Только исходные файлы
add_executable(lab3 
    main.cpp 
    TrigonometricEquationSolver.cpp
    TrigonometricEquationSolver.h
)

# Устанавливаем выходной файл
set_target_properties(lab3 PROPERTIES OUTPUT_NAME "proram")