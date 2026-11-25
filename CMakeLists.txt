cmake_minimum_required(VERSION 3.16)
project(zero_copy_num_pipeline LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(output_executable 
    src/main.cpp
    src/pipeline_ops.cpp
    src/benchmark.cpp
)

target_include_directories(output_executable PRIVATE 
    include)

if(MSVC)
    target_compile_options(output_executable PRIVATE /W4 /WX)
else()
    target_compile_options(output_executable PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

