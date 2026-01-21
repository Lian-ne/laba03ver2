cmake_minimum_required(VERSION 3.10)
project(laba03ver2)

# Установите стандарт C++ (рекомендую 17 или 20)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Включите необходимые флаги компиляции
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Если хотите включить clang-tidy
# set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*")

# Добавьте исполняемый файл main
add_executable(main
    main.cpp
    Dictionary.cpp
)

# Если у вас есть заголовочные файлы в текущей директории
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Если нужны дополнительные библиотеки
# find_package(some_library REQUIRED)
# target_link_libraries(main PRIVATE some_library)
