cmake_minimum_required(VERSION 3.16)
project(Disassembler)

set(CMAKE_CXX_STANDARD 20)

add_executable(Disassembler main.cpp Disassembler.cpp)
target_include_directories(Disassembler PUBLIC C:\\Programming\\projects\\onegin2)
target_include_directories(Disassembler PUBLIC C:\\Programming\\projects\\CPU2\\Common)

find_library(ONEGIN_LIBRARY objects lib)
target_link_libraries(Disassembler LINK_PUBLIC ${ONEGIN_LIBRARY})
