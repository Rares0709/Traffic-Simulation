cmake_minimum_required(VERSION 3.30)
project(untitled1)

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Werror -O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -Werror -O2")

set(CMAKE_EXE_LINKER_FLAGS -pthread)

if(WIN32)
    set(GTEST_INCLUDE_DIRS ./gtest/include)
    set(GTEST_LIB_DIRS ./gtest/libwin)
else()
    set(GTEST_INCLUDE_DIRS ../gtest/include)
    set(GTEST_LIB_DIRS ../gtest/lib)
endif()

include_directories(${GTEST_INCLUDE_DIRS})
link_directories(${GTEST_LIB_DIRS})

if(WIN32)
    include_directories(src src/Windows)
else()
    include_directories(src src/Linux)
endif()

set(SHARED_SOURCE_FILES
        src/tinystr.cpp
        src/tinyxmlerror.cpp
        src/tinystr.h
        src/tinyxml.h
        src/tinyxml.cpp
        src/tinyxmlparser.cpp
        src/ParseFile.cpp
        src/ParseFile.h
        src/TrafficSimulation.cpp
        src/TrafficSimulation.h
        src/structs.cpp
        src/structs.h
        src/Classes/Baan.h
        src/Classes/Bushalte.h
        src/Classes/Kruispunt.h
        src/Classes/Verkeersverkeerslicht.h
        src/Classes/Voertuig.h
        src/Classes/VoertuigGen.h
        src/Classes/Baan.cpp
        src/Classes/Bushalte.cpp
        src/Classes/Kruispunt.cpp
        src/Classes/Verkeersverkeerslicht.cpp
        src/Classes/Voertuig.cpp
        src/Classes/VoertuigGen.cpp
)

if(WIN32)
    list(APPEND SHARED_SOURCE_FILES src/Windows/DesignByContract.h)
else()
    list(APPEND SHARED_SOURCE_FILES src/Linux/DesignByContract.h)
endif()

set(RELEASE_SOURCE_FILES src/main.cpp ${SHARED_SOURCE_FILES})
set(DEBUG_SOURCE_FILES src/tests.cpp ${SHARED_SOURCE_FILES})

add_executable(Traffic-Simulation ${RELEASE_SOURCE_FILES})
add_executable(TS ${DEBUG_SOURCE_FILES})
target_link_libraries(TS gtest)

add_custom_target(clean-all
        COMMAND ${CMAKE_MAKE_PROGRAM} clean
        COMMAND ${CMAKE_COMMAND} -E rm -rf doc/html
        COMMENT "Cleaning project and removing Doxygen documentation"
)