cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")
project(GOL)

add_subdirectory (src)


#--------------
# GTest
#
ADD_SUBDIRECTORY (ext/googletest-read-only)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#--------------
# Unit Tests
#

# Add test cpp file
add_executable( run_unit_tests test/board_test.cpp )

# Link test executable against gtest & gtest_main
target_link_libraries(run_unit_tests gtest gtest_main)
add_test( run_unit_tests run_unit_tests )
