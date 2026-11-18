cmake_minimum_required(VERSION 3.15)
project(workable VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(shell
    src/main.cpp
    src/builtins.cpp
    src/shell_parser.cpp
    src/pathSearch.cpp
    src/executor.cpp)

if(MSVC)
  target_compile_options(shell PRIVATE /W4)
else()
  target_compile_options(shell PRIVATE -Wall -Wextra)
endif()