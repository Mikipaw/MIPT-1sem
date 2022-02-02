cmake_minimum_required(VERSION 3.16)
project(Assembler)

set(CMAKE_CXX_STANDARD 20)

add_executable(Assembler main.cpp Assembler.cpp)
target_include_directories(Assembler PUBLIC C:\\Programming\\projects\\onegin2)
target_include_directories(Assembler PUBLIC C:\\Programming\\projects\\CPU2\\Common)

find_library(ONEGIN_LIBRARY objects lib)
target_link_libraries(Assembler LINK_PUBLIC ${ONEGIN_LIBRARY})