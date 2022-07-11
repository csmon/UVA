cmake_minimum_required(VERSION 3.0.0)
project(uva VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(uva ./Volume_1/uva246.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library

target_link_libraries(uva ${GTEST_LIBRARIES} pthread)
