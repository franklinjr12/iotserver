cmake_minimum_required(VERSION 3.0)

project(${PROJNAME} LANGUAGE CXX)

set(SRCSFOLDER src)
set(INCLUDEFOLDER include)
set(DATASCTRUCTURESFOLDER datastructures)

find_package (Threads)

include_directories(${INCLUDEFOLDER})
include_directories(${DATASCTRUCTURESFOLDER})
# must export BOOSTFOLDER to the location of your boost installation
include_directories(${BOOSTFOLDER})
#file(GLOB SRCS "${SRCSFOLDER}/*.cpp")
list(APPEND SRCS "src/main.cpp")

add_executable(app.exe ${SRCS})
target_link_libraries (app.exe ${CMAKE_THREAD_LIBS_INIT})