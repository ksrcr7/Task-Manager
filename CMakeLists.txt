cmake_minimum_required(VERSION 3.15)
project(TaskManager CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# core library (Task + TaskManager)
add_library(taskcore
        src/lib/Task.cpp
        src/lib/TaskManager.cpp
        include/Task.h
        include/TaskManager.h
)

# main app (CLI + main)
add_executable(TaskManager_CLI
        src/main.cpp
        src/CLI.cpp
        src/CLI.h
)

target_link_libraries(TaskManager_CLI PRIVATE taskcore)

# warnings
if (MSVC)
    target_compile_options(taskcore PRIVATE /W4 /permissive-)
    target_compile_options(TaskManager_CLI PRIVATE /W4 /permissive-)
else()
    target_compile_options(taskcore PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(TaskManager_CLI PRIVATE -Wall -Wextra -Wpedantic)
endif()
