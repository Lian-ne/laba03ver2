cmake_minimum_required(VERSION 3.10)
project(laba03ver2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основной исполняемый файл (замените на ваши файлы)
add_executable(${PROJECT_NAME} main.cpp)

# Настройка clang-format (ДОБАВЬТЕ ЭТОТ БЛОК)
find_program(CLANG_FORMAT_EXE NAMES clang-format)
if(CLANG_FORMAT_EXE)
    # Получаем все C/C++ файлы в проекте
    file(GLOB_RECURSE ALL_SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/src/*.cpp
        ${CMAKE_SOURCE_DIR}/src/*.h
        ${CMAKE_SOURCE_DIR}/include/*.h
        ${CMAKE_SOURCE_DIR}/*.cpp
        ${CMAKE_SOURCE_DIR}/*.h
    )

    # Цель для проверки форматирования
    add_custom_target(clang-format-check
        COMMAND ${CLANG_FORMAT_EXE}
        --style=file
        --dry-run
        --Werror
        ${ALL_SOURCE_FILES}
        COMMENT "Проверка форматирования clang-format"
    )

    # Цель для автоматического форматирования
    add_custom_target(clang-format-fix
        COMMAND ${CLANG_FORMAT_EXE}
        --style=file
        -i
        ${ALL_SOURCE_FILES}
        COMMENT "Автоматическое форматирование clang-format"
    )

    # Алиас для совместимости
    add_custom_target(clang-format
        DEPENDS clang-format-check
        COMMENT "Запуск проверки форматирования"
    )
else()
    message(WARNING "clang-format не найден. Цели clang-format не будут доступны.")
endif()
