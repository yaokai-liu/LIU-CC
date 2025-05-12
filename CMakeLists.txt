cmake_minimum_required(VERSION 3.31)
project(liu-cc C)

set(CMAKE_C_STANDARD 23)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/output)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

#add_compile_options("-O3" "-Os")
add_compile_options("-funsigned-char" "-fno-builtin")
add_compile_options("-Wall" "-Wextra" "-Werror")
if (WIN32)
    add_compile_options("-Wno-format")
endif ()
if (ENABLE_TEST_COV)
    add_compile_options("-fprofile-arcs" "-ftest-coverage")
endif ()
if (ENABLE_GPROF)
    add_compile_options("-pg")
    add_link_options("-pg")
endif ()

set(GENERATED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/grammar/generated")
if(NOT EXISTS ${GENERATED_DIR})
    message(STATUS "${GENERATED_DIR} doesn't exist, generate grammar action table.")
    execute_process(COMMAND /bin/sh ${CMAKE_CURRENT_SOURCE_DIR}/codegen.sh
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
else()
    message(STATUS "${GENERATED_DIR} exists, skip to generate grammar action table.")
endif()

include_directories(meman)
aux_source_directory(meman MEMAN_SRC)
add_library(meman ${MEMAN_SRC})
link_libraries(meman)

file(GLOB_RECURSE GRAMMAR_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} grammar/*.c grammar/*.h)
add_library(grammar ${GRAMMAR_SRC})
target_include_directories(grammar PRIVATE grammar)

add_executable(liu-cc main.c)
target_link_libraries(liu-cc PRIVATE s
        grammar)
target_include_directories(liu-cc PRIVATE grammar)
