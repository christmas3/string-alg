cmake_minimum_required(VERSION 3.14)
project(archive_file)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")

add_executable(${PROJECT_NAME} main.cpp Rle.h Rle.cpp Kmp.h Kmp.cpp)
target_link_libraries(${PROJECT_NAME} pthread)

enable_testing()
add_subdirectory(test)
