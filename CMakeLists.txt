cmake_minimum_required(VERSION 3.0)

project(${PROJNAME} LANGUAGE CXX)

set(SRCSFOLDER src)
set(INCLUDEFOLDER include)
set(DATASCTRUCTURESFOLDER datastructures)

find_package (Threads)
find_package (Boost)

list(APPEND SRCS src/main.cpp src/receiver.cpp)
include_directories(${INCLUDEFOLDER})
include_directories(${DATASCTRUCTURESFOLDER})

# must export BOOSTFOLDER to the location of your boost installation
include_directories(${BOOSTFOLDER})
link_directories(${BOOSTFOLDER}/stage/lib)

add_executable(app.exe ${SRCS})
target_link_libraries (app.exe ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(app.exe boost_system boost_thread boost_chrono)

# add debug flags to the executable
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g -O0")