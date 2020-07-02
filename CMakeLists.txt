cmake_minimum_required(VERSION 3.13)
project(readers_and_writers VERSION 0.1.0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic")

include(CTest)
enable_testing()

add_executable(readers_and_writers src/main.cpp)
target_compile_features(readers_and_writers PUBLIC cxx_std_17)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
