cmake_minimum_required(VERSION 3.14)

set(TEST_EXECUTABLE "${PROJECT_NAME}Test")

add_executable(${TEST_EXECUTABLE} ${PROJECT_SOURCE_DIR}/StringAlg.h ${PROJECT_SOURCE_DIR}/test/StringTest.cpp ${PROJECT_SOURCE_DIR}/Bm.h ${PROJECT_SOURCE_DIR}/Bm.cpp ${PROJECT_SOURCE_DIR}/Kmp.cpp ${PROJECT_SOURCE_DIR}/Kmp.h ${PROJECT_SOURCE_DIR}/VectorArray.h ${PROJECT_SOURCE_DIR}/test/ArchiveTest.cpp ${PROJECT_SOURCE_DIR}/Rle.h ${PROJECT_SOURCE_DIR}/Rle.cpp ${PROJECT_SOURCE_DIR}/test/main.cpp)

target_link_libraries(${TEST_EXECUTABLE} gtest_main gtest pthread)

include(GoogleTest)
gtest_discover_tests(${TEST_EXECUTABLE})
