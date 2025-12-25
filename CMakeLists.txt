cmake_minimum_required(VERSION 3.10)
project(laba03ver2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основной исполняемый файл
add_executable(${PROJECT_NAME} main.cpp)

# Настройка clang-format с исключением build папки
find_program(CLANG_FORMAT_EXE NAMES clang-format)
if(CLANG_FORMAT_EXE)
    # Исключаем build папку и другие сгенерированные файлы
    file(GLOB_RECURSE ALL_SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/*.cpp
        ${CMAKE_SOURCE_DIR}/*.h
        ${CMAKE_SOURCE_DIR}/*.hpp
        ${CMAKE_SOURCE_DIR}/src/*.cpp
        ${CMAKE_SOURCE_DIR}/src/*.h
        ${CMAKE_SOURCE_DIR}/include/*.h
        ${CMAKE_SOURCE_DIR}/include/*.hpp
    )

    # Фильтруем файлы, исключая build папку
    set(FILTERED_SOURCE_FILES)
    foreach(FILE ${ALL_SOURCE_FILES})
        # Исключаем файлы из папки build и .git
        if(NOT FILE MATCHES "${CMAKE_SOURCE_DIR}/build/"
           AND NOT FILE MATCHES "${CMAKE_SOURCE_DIR}/\\.git/")
            list(APPEND FILTERED_SOURCE_FILES ${FILE})
        endif()
    endforeach()

    # Цель для проверки форматирования
    add_custom_target(clang-format-check
        COMMAND ${CLANG_FORMAT_EXE}
        --style=file
        --dry-run
        --Werror
        ${FILTERED_SOURCE_FILES}
        COMMENT "Проверка форматирования clang-format"
    )

    # Цель для автоматического форматирования
    add_custom_target(clang-format-fix
        COMMAND ${CLANG_FORMAT_EXE}
        --style=file
        -i
        ${FILTERED_SOURCE_FILES}
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
