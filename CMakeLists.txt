cmake_minimum_required(VERSION 3.10)
project(laba03ver2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Исполняемый файл
add_executable(main
    main.cpp
    Dictionary.cpp
)

# Добавьте цель clang-format
find_program(CLANG_FORMAT_EXE "clang-format")
if(CLANG_FORMAT_EXE)
    # Найти все исходные файлы
    file(GLOB_RECURSE ALL_SOURCE_FILES
        "*.cpp"
        "*.hpp"
        "*.h"
        "*.c"
    )

    # Исключить некоторые папки если нужно
    # list(FILTER ALL_SOURCE_FILES EXCLUDE REGEX ".*/build/.*")

    # Создать цель для форматирования
    add_custom_target(clang-format
        COMMAND ${CLANG_FORMAT_EXE}
        -style=file
        -i
        ${ALL_SOURCE_FILES}
        COMMENT "Running clang-format"
    )

    # Также можно добавить цель для проверки
    add_custom_target(clang-format-check
        COMMAND ${CLANG_FORMAT_EXE}
        -style=file
        --dry-run
        --Werror
        ${ALL_SOURCE_FILES}
        COMMENT "Checking clang-format"
    )
else()
    message(WARNING "clang-format not found!")
endif()
