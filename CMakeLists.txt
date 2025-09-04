find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
    file(GLOB_RECURSE SOURCE_FILES ".cpp" ".h")
    if(SOURCE_FILES)
        add_custom_target(clang-format
            COMMAND ${CLANG_FORMAT} -i --style=file ${SOURCE_FILES}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Formatting code with clang-format"
        )
    else()
        add_custom_target(clang-format
            COMMAND echo "No source files found for formatting"
            COMMENT "clang-format: no files to format"
        )
    endif()
else()
    add_custom_target(clang-format
        COMMAND echo "clang-format not found"
        COMMENT "clang-format: tool not available"
    )
endif()
