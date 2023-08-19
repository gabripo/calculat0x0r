cmake_minimum_required(VERSION 3.0.0)
project(calculat0x0r VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

add_executable(calculat0x0r src/main.c)
target_include_directories(calculat0x0r PUBLIC "include/")

set(CMAKE_C_COMPILER "clang")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_test(NAME calculat0x0r_no_args COMMAND calculat0x0r)
