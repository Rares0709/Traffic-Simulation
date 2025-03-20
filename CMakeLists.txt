cmake_minimum_required(VERSION 3.30)
project(untitled1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Werror -O2")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

if(WIN32)
    set(GTEST_INCLUDE_DIRS ./gtest/include)
    set(GTEST_LIB_DIRS ./gtest/lib)
else()
    set(GTEST_INCLUDE_DIRS ../gtest/include)
    set(GTEST_LIB_DIRS ../gtest/lib)
endif()

include_directories(${GTEST_INCLUDE_DIRS})
link_directories(${GTEST_LIB_DIRS})

set(RELEASE_SOURCE_FILES main.cpp
        tinystr.cpp
        tinyxmlerror.cpp
        tinystr.h
        tinyxml.h
        tinyxml.cpp
        tinyxmlparser.cpp)

set(DEBUG_SOURCE_FILES main.cpp
        tinystr.cpp
        tinyxmlerror.cpp
        tinystr.h
        tinyxml.h
        tinyxml.cpp
        tinyxmlparser.cpp
        tests.cpp)

add_executable(Traffic-Simulation ${RELEASE_SOURCE_FILES})
add_executable(TS ${DEBUG_SOURCE_FILES})

target_link_libraries(TS gtest)

add_custom_target(clean-all
        COMMAND ${CMAKE_MAKE_PROGRAM} clean
        COMMAND ${CMAKE_COMMAND} -E rm -rf doc/html
        COMMENT "Cleaning project and removing Doxygen documentation"
)
