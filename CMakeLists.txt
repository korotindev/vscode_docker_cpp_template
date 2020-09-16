cmake_minimum_required(VERSION 3.16.3)
project(freq VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(ASAN_OPTIONS detect_leaks=1)
add_definitions(-D_LIBCPP_DEBUG)

include (cmake/cppcheck.cmake)
include (cmake/clang-format.cmake)

add_custom_target(run COMMAND bin/freq)

add_executable(freq src/main.cpp)
target_compile_features(freq PUBLIC cxx_std_17)
target_link_libraries(freq pthread)