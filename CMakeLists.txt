cmake_minimum_required(VERSION 3.10)
project(lab_3)

# Устанавливаем стандарт C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Флаги компилятора
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic")

# Находим все исходные файлы
file(GLOB SOURCES "*.cpp")

# Создаем исполняемый файл
add_executable(lab_3 ${SOURCES})

# Устанавливаем выходной файл (опционально)
set_target_properties(lab_3 PROPERTIES OUTPUT_NAME "program")