cmake_minimum_required(VERSION 2.6)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests tests.cpp mincut.h)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread boost_system)
target_compile_features(runTests PRIVATE cxx_range_for)
