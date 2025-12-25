cmake_minimum_required(VERSION 3.10)
project(laba03ver2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Для Clang-Tidy в CI
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Добавляем исполняемый файл
add_executable(${PROJECT_NAME}
    main.cpp  # если main.cpp в корне
    # или
    # src/main.cpp  # если в папке src
)
